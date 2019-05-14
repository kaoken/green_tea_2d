/*! @file  templates.h
 * @brief �e���v���[�g�֘A����Ɉ���
 * @author kaoken
 * @date 2014/01/17 �쐬�J�n
 */
#pragma once

/**
	* �V���O���g���e���v���[�g�N���X
	* @tparam T �^
	*/
template <typename T> class CSingleton
{
private:
	static T* ms_pSingleton;

public:
	/*!
	* @brief �f�X�g���N�^
	*/
	CSingleton()
	{
		assert(!ms_pSingleton);
		ms_pSingleton = (T*)(this);
	}
	/*!
	* @brief �R���X�g���N�^
	*/
	~CSingleton()
	{
		assert(ms_pSingleton);  ms_pSingleton = nullptr;
	}

	/*!
	* @brief �V���O���g���|�C���^�̃Z�b�g
	*/
	inline static void SetSingletonPtr(T* my)
	{
		ms_pSingleton = my;
	}
	/*!
	* @brief ���M�̎Q�Ƃ��擾
	* @return ���M�̎Q�Ƃ��擾
	*/
	inline static T& GetSingleton()
	{
		assert(ms_pSingleton);  return (*ms_pSingleton);
	}
	/*!
	* @brief �V���O���g���|�C���^�̎擾
	* @return ���M�̃|�C���^���擾
	*/
	inline static T* GetSingletonPtr()
	{
		return (ms_pSingleton);
	}
};
template <typename T> T* CSingleton <T>::ms_pSingleton = nullptr;


/**
* �P���ȋ��L�|�C���^�}�l�[�W���[
* @tparam _T_INT �����̌^
* @tparam _T_SP  ���L�|�C���^ shared_ptr
*/
template <typename _T_INT, class TargetClass> class SimpleSharedPtrMgr
{
	int m_num;
	std::map< _T_INT, TargetClass>	m_map;
public:
	typedef typename std::map< _T_INT, TargetClass>::iterator iterator;
public:
	//! �R���X�g���N�^
	SimpleSharedPtrMgr()
	{
		m_num = 1;
	}
	inline TargetClass& operator[](_T_INT idx) {
		return m_map[idx];
	}
	/**
		* ������Ԃ��B
		* @return ����
		*/
	inline uint32_t len()
	{
		return m_map.size();
	}
	/**
	* �����B
	* @param [in] n �ԍ�
	* @return ���������ꍇtrue��Ԃ��B
	*/
	inline bool erase(_T_INT n)
	{
		return m_map.erase(n) != 0;
	}
	/**
	* �T��
	* @param [in] n �ԍ�
	* @return �������ꍇtrue��Ԃ��B
	*/
	inline bool find(_T_INT n)
	{
		iterator i;
		if ((i = m_map.find(n)) == m_map.end())return false;
		return true;
	}
	/**
	* �}�b�v�E�R���e�i���̍ŏ��̗v�f���Q�Ƃ��锽���q��Ԃ��܂��B
	* @return �����q��Ԃ��B
	*/
	inline iterator begin()
	{
		return m_map.begin();
	}
	/**
	* �}�b�v�R���e�i�̉ߋ��E�G���h�̗v�f���Q�Ƃ��锽���q��Ԃ��܂��B
	* @return �����q��Ԃ��B
	*/
	inline iterator end()
	{
		return m_map.end();
	}
	/**
	* �N���A����B
	*/
	void clear()
	{
		m_map.clear();
	}
	/**
	* �}������
	* @param [in] rSP ���L�|�C���^�^
	* @return ���݂̑}�����ꂽ�ʒu�iid�j��Ԃ��B
	*/
	_T_INT insert(TargetClass &rSP)
	{
		std::pair<iterator, bool> rc;
		rc = m_map.insert(mcMkPair(m_num, rSP));
		if (rc.second) {
			//---- �V�����}��
			++m_num;
		}
		else {
			//---- ���łɑ��݂���
			return 0;
		}
		return m_num - 1;
	}
};


//-----------------------------------------
//! @brief GenericObjectFactory�Ŏg�p����
//! @see GenericObjectFactory
//! @tparam BaseClass ��{�N���X
//! @tparam SubType   �C�ӂ̌^��\��id
//-----------------------------------------
template <class BaseType, class SubType>
BaseType* GenericObjectCreationFunction() { return new SubType; }

//-----------------------------------------
//! @brief �t�@�N�g���[
//!
//! @tparam BaseClass ��{�N���X
//! @tparam IdType    �C�ӂ̌^��\��id
//-----------------------------------------
template <class BaseClass, class IdType>
class GenericObjectFactory
{
	typedef BaseClass* (*ObjectCreationFunction)(void);
	std::map<IdType, ObjectCreationFunction> m_creationFunctions;

public:
	//-----------------------------------------
	//! �C�ӂ̃N���X��id��o�^����
	//! @param  id 
	//! @tparam SubClass �C�ӂ̃N���X
	//! @return �o�^�ɐ��������ꍇ��true��Ԃ�
	//-----------------------------------------
	template <class SubClass>
	bool Register(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt == m_creationFunctions.end())
		{
			m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;
			return true;
		}

		return false;
	}
	//-----------------------------------------
	//! �w��id����C�ӂ̃N���X�����
	//! @param  id 
	//! @return ���������ꍇ�͂��̃|�C���^��Ԃ��B
	//-----------------------------------------
	BaseClass* Create(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt != m_creationFunctions.end())
		{
			ObjectCreationFunction pFunc = findIt->second;
			return pFunc();
		}

		return nullptr;
	}
};

////////////////////////////////////////
// COM�p���w���p�[�B

// COM�I�u�W�F�N�g��������A�|�C���^�𖳌��ɂ��܂��B
template <typename InterfaceType>
inline void SafeRelease(InterfaceType** currentObject)
{
	if (*currentObject != nullptr)
	{
		(*currentObject)->Release();
		*currentObject = nullptr;
	}
}


// ��null�̏ꍇ�́A�ǉ��̎Q�Ƃ��擾���܂��B
template <typename InterfaceType>
inline InterfaceType* SafeAcquire(InterfaceType* newObject)
{
	if (newObject != nullptr)
		newObject->AddRef();

	return newObject;
}


// �V����COM�I�u�W�F�N�g��ݒ肵�A�Â�COM�I�u�W�F�N�g��������܂��B
template <typename InterfaceType>
inline void SafeSet(InterfaceType** currentObject, InterfaceType* newObject)
{
	SafeAcquire(newObject);
	SafeRelease(&currentObject);
	currentObject = newObject;
}


// ������HRESULT�ւ̗�O�̃}�b�v
inline HRESULT ExceptionToHResult() throw()
{
	try
	{
		throw;  // Rethrow previous exception.
	}
	catch (std::bad_alloc&)
	{
		return E_OUTOFMEMORY;
	}
	catch (...)
	{
		return E_FAIL;
	}
}
