/*
 * All the base classes required for lostl.
 * All classes derive either from reference_type or value_type.
 * value_types always contain a sub-type which is always cloned on copy.
 * You can
 * reference_types 
*/

namespace lolibc
{
	class object;
	class reference_type;

	class ref_base
	{
	public:
		ref_base();
		ref_base(object *obj);
		virtual ~ref_base();
	protected:
		object	*m_obj;
	};

	template <typename T>
	class ref : public ref_base
	{
	public:
		ref() : ref_base() {}
		ref(const T& obj) : ref_base(&obj)	{  }
		ref(const T* obj) : ref_base(obj)	{  }
		inline ref( ref<T> & external ) : BaseRef(external.ptr) {}
		inline T* operator->()				{ return (reinterpret_cast<T *>(ptr)); }
		inline T *Ptr() const				{ return reinterpret_cast<T*>(ptr); }
	private:
	};
}

namespace std
{
	class string;
	template<typename T>	class vector;
}

namespace lolibc
{
	int GetHashCode(const unsigned char *buffer,size_t len);

	class object
	{
		friend class ref_base;
	public:
		virtual ~object();
		inline virtual int			GetHashCode() const	{ return 0; }
		virtual ref<::std::string>	ToString();
	private:
		ref<::std::vector<ref_base *>>	m_references;
	};

	/*!
	\brief value_type always copies its value.
	T = class name, TValue = value type name, i.e. "bool"
	Derive your value_type from this class.
	 */
	template <class T,typename TValue>
	class value_type : public object
	{
	public:
		virtual int CompareTo(const Object &obj) const
		{
			if( const ValueType<T,TValue> * t = dynamic_cast<const ValueType<T,TValue> *>(&obj) )
				return CompareTo(*t);
			return 1;
		}
		virtual bool Equals(const Object &obj) const
		{
			if( const ValueType<T,TValue> * t = dynamic_cast<const ValueType<T,TValue> *>(&obj) )
				return Equals(*t);
			return false;
		}
		virtual bool Equals(const T &obj) const
		{
			return (m_value==obj.m_value) != 0;
		}
		inline bool	operator== (const T &obj) const
		{
			return m_value==obj.m_value;
		}
		inline bool	operator!= (const T &obj) const
		{
			return m_value!=obj.m_value;
		}
		inline operator TValue()	{ return m_value; }
		inline const TValue *		GetPointer() const	{ return &m_value; }
		inline size_t				ValueSize()	const	{ return sizeof(TValue); }
		ref<object>					Clone()				{ return ref<object>(static_cast<object *>(new T(m_value))); }
		virtual int					GetHashCode() const	{ return ::lolibc::GetHashCode(reinterpret_cast<const unsigned char *>(GetPointer()), ValueSize()); }
	protected:
		inline ValueType()	{}
		inline ValueType(const TValue value) : m_value(value)	{}
		TValue				m_value;
	};
}
