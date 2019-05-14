#pragma once

#include <Core/greenTea2D.h>
#include <Math/vector.h>
#include <Math/matrix.h>


//-----------------------------------------------------------------------------------
//! @brief �ϐ��̌^�l
//-----------------------------------------------------------------------------------
enum gt2UtilValueType
{
	__NONE = 0,				//!< ����
	__FLOAT,				//!< float�^ �P��
	__FLOAT2,				//!< float�^ �Q��
	__VEC_F2 = __FLOAT2,	//!< gt2Vector2
	__FLOAT3,				//!< float�^ �R��
	__VEC_F3 = __FLOAT3,	//!< gt2Vector3
	__FLOAT4,				//!< float�^ �S��
	__VEC_F4 = __FLOAT4,	//!< gt2Vector4
	__FLOAT4x4,				//!< flaot�^ �}�g���N�X�P��
	__ARY_FLOAT4x4,			//!< flaot�^ �}�g���N�X �z��
	__ARY_FLOAT,			//!< float�^ �z��
	__BOOL,					//!< bool�^ �P��
	__ARY_BOOL,				//!< bool�^ �z��
	__INT,					//!< int�^ �P��
	__ARY_INT,				//!< int�^ �z��
	__DOUBLE,				//!< double�^ �P��
	__ARY_DOUBLE,			//!< double�^ �z��
	__END_TYPE,				//!< 
};

//-----------------------------------------------------------------------------------
//! @brief 
//-----------------------------------------------------------------------------------
class GT2UtilValue
{
protected:
	gt2UtilValueType m_type;		//!< �^�̃^�C�v
	gtUINT m_size;				//!< �ϐ��̃T�C�Y
	gtUINT m_aryNum;			//!< �z��
	union{
		void		*_p;		//!< �_�~�[
		bool		*_pBool;	//!< bool�^�|�C���^
		float		*_pFloat;	//!< float�^�|�C���^
		int			*_pInt;		//!< int�^�|�C���^
		double		*_pDouble;	//!< double�^�|�C���^
	};
public:
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	GT2UtilValue()
	{
		m_type = __NONE;
		_p = nullptr;
		m_size = 0;
		m_aryNum = 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �f�X�g���N�^
	//-----------------------------------------------------------------------------------
	~GT2UtilValue()
	{
		SAFE_DELETE_ARRAY(_pFloat);
	}
	//-----------------------------------------------------------------------------------
	//! @brief ������Z�q:r���R�s�[�������̂�Ԃ�
	//! @param [in] r GT2UtilValue
	//! @return GT2UtilValue
	//-----------------------------------------------------------------------------------
	inline GT2UtilValue& operator = (const GT2UtilValue& r)
	{
		if (__FLOAT <= m_type && __ARY_FLOAT >= m_type && _pFloat != nullptr)
		{
			delete[] _pFloat;
			_pFloat = nullptr;
		}
		this->Create(r.m_type, r.m_size);
		memcpy(_pFloat, r._pFloat, sizeof(float)*r.m_size);
		return *this;
	}
	//-----------------------------------------------------------------------------------
	//! @brief �w�肵���^�ŕϐ����쐬����
	//! @param [in] t       �^�̃^�C�v
	//! @param [in] aryNum t���z��̏ꍇ�A���̃T�C�Y
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool Create(gt2UtilValueType t, int aryNum = 0)
	{
		assert(!_p);
		if (_p != nullptr)return false;

		m_type = t;
		if (m_type == __FLOAT)
		{
			m_size = sizeof(float);
			_pFloat = new float[1];
		}
		else if (m_type == __FLOAT2 || m_type == __VEC_F2 )
		{
			m_size = sizeof(float)*2;
			_pFloat = new float[2];
		}
		else if (m_type == __FLOAT3 || m_type == __VEC_F3)
		{
			m_size = sizeof(float)*3;
			_pFloat = new float[3];
		}
		else if (m_type == __FLOAT4 || m_type == __VEC_F4)
		{
			m_size = sizeof(float)*4;
			_pFloat = new float[4];
		}
		else if (m_type == __INT)
		{
			m_size = sizeof(int32_t);
			_pInt = new int32_t[1];
		}
		else if (m_type == __BOOL)
		{
			m_size = sizeof(bool);
			_pBool = new bool[1];
		}
		else if (m_type == __DOUBLE)
		{
			m_size = sizeof(double);
			_pDouble = new double[1];
		}
		else if (m_type == __FLOAT4x4)
		{
			m_size = sizeof(float)* 16;
			_pFloat = new float[16];
		}
		else if (m_type == __ARY_FLOAT)
		{
			if (aryNum < 1)return false;
			_pFloat = new float[aryNum];
			m_size = sizeof(float)*aryNum;
			m_aryNum = aryNum;
		}
		else if (m_type == __ARY_BOOL)
		{
			if (aryNum < 1)return false;
			_pBool = new bool[aryNum];
			m_size = sizeof(bool)*aryNum;
			m_aryNum = aryNum;
		}
		else if (m_type == __ARY_INT)
		{
			if (aryNum < 1)return false;
			_pInt = new int32_t[aryNum];
			m_size = sizeof(int32_t)*aryNum;
			m_aryNum = aryNum;
		}
		else if (m_type == __ARY_DOUBLE)
		{
			if (aryNum < 1)return false;
			_pDouble = new double[aryNum];
			m_size = sizeof(double)*aryNum;
			m_aryNum = aryNum;
		}
		else if (m_type == __ARY_FLOAT4x4)
		{
			if (aryNum < 1)return false;
			_pFloat = new float[16*aryNum];
			m_size = sizeof(float)*aryNum*16;
			m_aryNum = aryNum;
		}
			

		return _pFloat != nullptr;
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���ꂽ��ނ��擾
	//! @return ���ꂽ��ނ�Ԃ��B
	//-----------------------------------------------------------------------------------
	inline gt2UtilValueType GetType(){ return m_type; }
	//-----------------------------------------------------------------------------------
	//! @brief �z�񐔂�Ԃ��B�z��ō���Ă��Ȃ��ꍇ�́A0��Ԃ��B
	//! @return �z�񐔂�Ԃ��B
	//-----------------------------------------------------------------------------------
	inline gtUINT GetAryNum(){ return m_aryNum; }
	//-----------------------------------------------------------------------------------
	//! @brief �쐬�����ϐ��̑S�̃T�C�Y��Ԃ�
	//! @return �쐬�����ϐ��̑S�̃T�C�Y��Ԃ�
	//-----------------------------------------------------------------------------------
	inline gtUINT GetSize(){ return m_size; }
	//-----------------------------------------------------------------------------------
	//! @brief float�^�̃|�C���^���擾
	//! @return float�^�̃|�C���^��Ԃ��Bfloat�^�A�܂��́A����Ă��Ȃ��ꍇ��null��Ԃ�
	//-----------------------------------------------------------------------------------
	inline float* GetFloatPtr(){
		if ((int)m_type < (int)__FLOAT || (int)m_type > (int)__ARY_FLOAT)return nullptr;
		return _pFloat;
	}
	//-----------------------------------------------------------------------------------
	//! @brief bool�^�̃|�C���^���擾
	//! @return bool�^�̃|�C���^��Ԃ��Bbool�^�A�܂��́A����Ă��Ȃ��ꍇ��null��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool* GetBoolPtr(){
		if (m_type != __BOOL && m_type != __ARY_BOOL)return nullptr;
		return _pBool;
	}
	//-----------------------------------------------------------------------------------
	//! @brief int�^�̃|�C���^���擾
	//! @return int�^�̃|�C���^��Ԃ��Bint�^�A�܂��́A����Ă��Ȃ��ꍇ��null��Ԃ�
	//-----------------------------------------------------------------------------------
	inline int* GetIntPtr(){
		if (m_type != __INT && m_type != __ARY_INT)return nullptr;
		return _pInt;
	}
	//-----------------------------------------------------------------------------------
	//! @brief double�^�̃|�C���^���擾
	//! @return double�^�̃|�C���^��Ԃ��Bdouble�^�A�܂��́A����Ă��Ȃ��ꍇ��null��Ԃ�
	//-----------------------------------------------------------------------------------
	inline double* GetDoublePtr(){
		if (m_type != __DOUBLE && m_type != __ARY_DOUBLE)return nullptr;
		return _pDouble;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1��float�^�̒l���Z�b�g����
	//! @param [in] f �l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetFloat(float f){
		if (m_type != __FLOAT)return false;
		*_pFloat = f;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1��bool�^�̒l���Z�b�g����
	//! @param [in] n �l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetBool(bool n){
		if (m_type != __BOOL)return false;
		*_pBool = n;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1��int�^�̒l���Z�b�g����
	//! @param [in] n �l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetInt(int n){
		if (m_type != __INT)return false;
		*_pInt = n;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1��double�^�̒l���Z�b�g����
	//! @param [in] n �l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetDouble(double n){
		if (m_type != __DOUBLE)return false;
		*_pDouble = n;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2��float�^�̒l���Z�b�g����
	//! @param [in] f1 �l
	//! @param [in] f2 �l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetFloat2(float f1, float f2){
		if (m_type != __FLOAT2)return false;
		_pFloat[0] = f1; _pFloat[1] = f2;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief VectorF2�^�̒l���Z�b�g����
	//! @param [in] v VectorF2�l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetVectorF2(const gt2Vector2 & v){
		if (m_type != __FLOAT2)return false;
		memcpy(_pFloat, v.v, sizeof(gt2Vector2));
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 3��float�^�̒l���Z�b�g����
	//! @param [in] f1 �l
	//! @param [in] f2 �l
	//! @param [in] f3 �l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetFloat3(float f1, float f2, float f3){
		if (m_type != __FLOAT3)return false;
		_pFloat[0] = f1; _pFloat[1] = f2; _pFloat[2] = f3;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief VectorF3�^�̒l���Z�b�g����
	//! @param [in] v VectorF3�l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetVectorF3(const gt2Vector3 & v){
		if (m_type != __FLOAT3)return false;
		memcpy(_pFloat, v.v, sizeof(gt2Vector3));
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 4��float�^�̒l���Z�b�g����
	//! @param [in] f1 �l
	//! @param [in] f2 �l
	//! @param [in] f3 �l
	//! @param [in] f4 �l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetFloat4(float f1, float f2, float f3, float f4){
		if (m_type != __FLOAT4)return false;
		_pFloat[0] = f1; _pFloat[1] = f2; _pFloat[2] = f3; _pFloat[3] = f4;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief VectorF4�^�̒l���Z�b�g����
	//! @param [in] v VectorF4�l
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetVectorF4(const gt2Vector4 & v){
		if (m_type != __FLOAT4)return false;
		memcpy(_pFloat, v.v, sizeof(gt2Vector4));
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief float�^�̔z��̒l���Z�b�g����
	//! @param [in] pN    float�^�̔z��|�C���^
	//! @param [in] count �z��̃T�C�Y
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetFloatArray(const float *pN, gtUINT count){
		if (m_type != __ARY_FLOAT)return false;
		memcpy(_pFloat, pN, sizeof(float)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief int�^�̔z��̒l���Z�b�g����
	//! @param [in] pN    int�^�̔z��|�C���^
	//! @param [in] count �z��̃T�C�Y
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetIntArray(const int *pN, gtUINT count){
		if (m_type != __ARY_INT)return false;
		memcpy(_pInt, pN, sizeof(int)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief bool�^�̔z��̒l���Z�b�g����
	//! @param [in] pN    bool�^�̔z��|�C���^
	//! @param [in] count �z��̃T�C�Y
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetBoolArray(const bool *pN, gtUINT count){
		if (m_type != __ARY_BOOL)return false;
		memcpy(_pBool, pN, sizeof(bool)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief double�^�̔z��̒l���Z�b�g����
	//! @param [in] pN    double�^�̔z��|�C���^
	//! @param [in] count �z��̃T�C�Y
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetDoubleArray(const double *pN, gtUINT count){
		if (m_type != __ARY_DOUBLE)return false;
		memcpy(_pDouble, pN, sizeof(double)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2Matrix4x4�^�̔z��̒l���Z�b�g����
	//! @param [in] pM    gt2Matrix4x4�^�̔z��|�C���^
	//! @param [in] count �z��̃T�C�Y
	//! @return ���������ꍇtrue��Ԃ�
	//-----------------------------------------------------------------------------------
	inline bool SetMatrixF4x4Array(const gt2Matrix4x4 *pM, gtUINT count){
		if (m_type != __ARY_DOUBLE)return false;
		memcpy(_pFloat, pM, sizeof(gt2Matrix4x4)*count);
		return true;
	}
};
TYPEDEF_S_W_PTR(GT2UtilValue);
typedef gtMap<int, GT2UtilValueSP> gt2UtiValues;







//-----------------------------------------------------------------------------------
//! @brief �����̐��l���쐬����Ƃ��ɕ֗� @n
//!        �\���݂̂����Ȋ���
//-----------------------------------------------------------------------------------
class GT2UtilStructureValues
{
	friend class GT2UtilStructureValues;
	gt2UtiValues m_values;
public:
	//! �f�X�g���N�^
	virtual ~GT2UtilStructureValues() { }
	//-----------------------------------------------------------------------------------
	//! @brief GT2UtilStructureValues���m�̑�����Z�q
	//! @param [in] r GT2UtilStructureValues
	//! @return GT2UtilStructureValues
	//-----------------------------------------------------------------------------------
	GT2UtilStructureValues& operator = (const GT2UtilStructureValues& r)
	{
		// �폜
		m_values.clear();
		m_values.insert(r.m_values.begin(), r.m_values.end());

		return *this;
	}
	//-----------------------------------------------------------------------------------
	//! @brief idx �̏��Ԓʂ�� GT2UtilValue �����
	//! @param [in] idx     �C���f�b�N�X�l
	//! @param [in] type    �^�̎��
	//! @param [in] arySize �z��̃T�C�Y�B�f�t�H���g��0(�z��łȂ�)
	//! @retval ���������ꍇ�A0�ȏ�̑w�̒l��Ԃ��B
	//! @retval ���s�����ꍇ�A-1��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline bool Create(const int idx, gt2UtilValueType type, gtUINT arySize = 0)
	{
		if (m_values.find(idx) != m_values.end())return false;

		m_values.insert(gtMkPair(idx, GT2UtilValueSP(new GT2UtilValue())));

		return m_values[idx]->Create(type, arySize);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �w�肵���w��GT2UtilValueSP���擾����B
	//! @param [in] idx    �C���f�b�N�X
	//! @retval ���������ꍇ�AGT2UtilValueSP��Ԃ�
	//! @retval ���s�����ꍇ�Anullptr��Ԃ��B
	//-----------------------------------------------------------------------------------
	inline GT2UtilValueSP Get(gtUINT idx)
	{
		try {
			return m_values[idx];
		}
		catch (...) {
			return GT2UtilValueSP();
		}
	}
	//-----------------------------------------------------------------------------------
	//! @brief �ϐ��̐���Ԃ�
	//! @return �ϐ��̐�
	//-----------------------------------------------------------------------------------
	inline size_t Size() { return m_values.size(); }
	//-----------------------------------------------------------------------------------
	//! @brief ���̍\���̕ϐ��S�Ă�Ԃ�
	//! @return �ϐ��S�Ă�Ԃ�
	//-----------------------------------------------------------------------------------
	inline gt2UtiValues &GetValues() { return m_values; }
};
TYPEDEF_S_W_PTR(GT2UtilStructureValues);
