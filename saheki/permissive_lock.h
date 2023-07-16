#pragma once
#include <mutex>

namespace saheki
{

	template <typename _Mutex>
	class permissive_lock
	{
	public: // type
		typedef _Mutex mutex_type;

	private: // data
		mutex_type *my_mutex;
		bool mutex_owned;

	public: // constructors// 8/5/22
		explicit permissive_lock(mutex_type &_mtx) : my_mutex(std::__addressof(_mtx)), mutex_owned(false)
		{
			log::warnning("permissive_lock is in development");
			mutex_owned = my_mutex->try_lock();
		}
		~permissive_lock()
		{
			if (mutex_owned)
				unlock();
		}

	public: // operators
		permissive_lock(const permissive_lock &) = delete;
		permissive_lock(permissive_lock &&perm_lock) noexcept : my_mutex(perm_lock.my_mutex), mutex_owned(perm_lock.mutex_owned)
		{
			perm_lock.release();
		}
		permissive_lock &operator=(const permissive_lock &) = delete;
		permissive_lock &operator=(permissive_lock &&perm_lock) noexcept
		{
			if (mutex_owned)
				unlock();
			permissive_lock(std::move(perm_lock)).swap(*this);
			perm_lock.release();
			return *this;
		}

	public: // metods
		bool lock()
		{
			if (!my_mutex)
				return false;
			if (mutex_owned)
				return false;
			my_mutex->lock();
			mutex_owned = true;
			return true;
		}
		bool try_lock()
		{
			if (!my_mutex)
				return false;
			if (mutex_owned)
				return false;
			mutex_owned = my_mutex->try_lock();
			return mutex_owned;
		}
		bool unlock()
		{
			if (!my_mutex)
				return false;
			if (!mutex_owned)
				return false;
			my_mutex->unlock();
			mutex_owned = false;
			return true;
		}
		bool owns_lock() const noexcept
		{
			return mutex_owned;
		}
		mutex_type *mutex() const noexcept
		{
			return my_mutex;
		}
		void release()
		{
			my_mutex = 0;
			mutex_owned = false;
		}
	};

} // namespace end
