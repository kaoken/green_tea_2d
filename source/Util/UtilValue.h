#pragma once

#include <Core/greenTea2D.h>
#include <Math/vector.h>
#include <Math/matrix.h>


//-----------------------------------------------------------------------------------
//! @brief 変数の型値
//-----------------------------------------------------------------------------------
enum gt2UtilValueType
{
	__NONE = 0,				//!< 無し
	__FLOAT,				//!< float型 １つ
	__FLOAT2,				//!< float型 ２つ
	__VEC_F2 = __FLOAT2,	//!< gt2Vector2
	__FLOAT3,				//!< float型 ３つ
	__VEC_F3 = __FLOAT3,	//!< gt2Vector3
	__FLOAT4,				//!< float型 ４つ
	__VEC_F4 = __FLOAT4,	//!< gt2Vector4
	__FLOAT4x4,				//!< flaot型 マトリクス１つ
	__ARY_FLOAT4x4,			//!< flaot型 マトリクス 配列
	__ARY_FLOAT,			//!< float型 配列
	__BOOL,					//!< bool型 １つ
	__ARY_BOOL,				//!< bool型 配列
	__INT,					//!< int型 １つ
	__ARY_INT,				//!< int型 配列
	__DOUBLE,				//!< double型 １つ
	__ARY_DOUBLE,			//!< double型 配列
	__END_TYPE,				//!< 
};

//-----------------------------------------------------------------------------------
//! @brief 
//-----------------------------------------------------------------------------------
class GT2UtilValue
{
protected:
	gt2UtilValueType m_type;		//!< 型のタイプ
	gtUINT m_size;				//!< 変数のサイズ
	gtUINT m_aryNum;			//!< 配列数
	union{
		void		*_p;		//!< ダミー
		bool		*_pBool;	//!< bool型ポインタ
		float		*_pFloat;	//!< float型ポインタ
		int			*_pInt;		//!< int型ポインタ
		double		*_pDouble;	//!< double型ポインタ
	};
public:
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	GT2UtilValue()
	{
		m_type = __NONE;
		_p = nullptr;
		m_size = 0;
		m_aryNum = 0;
	}
	//-----------------------------------------------------------------------------------
	//! @brief デストラクタ
	//-----------------------------------------------------------------------------------
	~GT2UtilValue()
	{
		SAFE_DELETE_ARRAY(_pFloat);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 代入演算子:rをコピーしたものを返す
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
	//! @brief 指定した型で変数を作成する
	//! @param [in] t       型のタイプ
	//! @param [in] aryNum tが配列の場合、そのサイズ
	//! @return 成功した場合trueを返す
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
	//! @brief 作られた種類を取得
	//! @return 作られた種類を返す。
	//-----------------------------------------------------------------------------------
	inline gt2UtilValueType GetType(){ return m_type; }
	//-----------------------------------------------------------------------------------
	//! @brief 配列数を返す。配列で作られていない場合は、0を返す。
	//! @return 配列数を返す。
	//-----------------------------------------------------------------------------------
	inline gtUINT GetAryNum(){ return m_aryNum; }
	//-----------------------------------------------------------------------------------
	//! @brief 作成した変数の全体サイズを返す
	//! @return 作成した変数の全体サイズを返す
	//-----------------------------------------------------------------------------------
	inline gtUINT GetSize(){ return m_size; }
	//-----------------------------------------------------------------------------------
	//! @brief float型のポインタを取得
	//! @return float型のポインタを返す。float型、または、作られていない場合はnullを返す
	//-----------------------------------------------------------------------------------
	inline float* GetFloatPtr(){
		if ((int)m_type < (int)__FLOAT || (int)m_type > (int)__ARY_FLOAT)return nullptr;
		return _pFloat;
	}
	//-----------------------------------------------------------------------------------
	//! @brief bool型のポインタを取得
	//! @return bool型のポインタを返す。bool型、または、作られていない場合はnullを返す
	//-----------------------------------------------------------------------------------
	inline bool* GetBoolPtr(){
		if (m_type != __BOOL && m_type != __ARY_BOOL)return nullptr;
		return _pBool;
	}
	//-----------------------------------------------------------------------------------
	//! @brief int型のポインタを取得
	//! @return int型のポインタを返す。int型、または、作られていない場合はnullを返す
	//-----------------------------------------------------------------------------------
	inline int* GetIntPtr(){
		if (m_type != __INT && m_type != __ARY_INT)return nullptr;
		return _pInt;
	}
	//-----------------------------------------------------------------------------------
	//! @brief double型のポインタを取得
	//! @return double型のポインタを返す。double型、または、作られていない場合はnullを返す
	//-----------------------------------------------------------------------------------
	inline double* GetDoublePtr(){
		if (m_type != __DOUBLE && m_type != __ARY_DOUBLE)return nullptr;
		return _pDouble;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1つのfloat型の値をセットする
	//! @param [in] f 値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetFloat(float f){
		if (m_type != __FLOAT)return false;
		*_pFloat = f;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1つのbool型の値をセットする
	//! @param [in] n 値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetBool(bool n){
		if (m_type != __BOOL)return false;
		*_pBool = n;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1つのint型の値をセットする
	//! @param [in] n 値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetInt(int n){
		if (m_type != __INT)return false;
		*_pInt = n;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 1つのdouble型の値をセットする
	//! @param [in] n 値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetDouble(double n){
		if (m_type != __DOUBLE)return false;
		*_pDouble = n;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 2つのfloat型の値をセットする
	//! @param [in] f1 値
	//! @param [in] f2 値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetFloat2(float f1, float f2){
		if (m_type != __FLOAT2)return false;
		_pFloat[0] = f1; _pFloat[1] = f2;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief VectorF2型の値をセットする
	//! @param [in] v VectorF2値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetVectorF2(const gt2Vector2 & v){
		if (m_type != __FLOAT2)return false;
		memcpy(_pFloat, v.v, sizeof(gt2Vector2));
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 3つのfloat型の値をセットする
	//! @param [in] f1 値
	//! @param [in] f2 値
	//! @param [in] f3 値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetFloat3(float f1, float f2, float f3){
		if (m_type != __FLOAT3)return false;
		_pFloat[0] = f1; _pFloat[1] = f2; _pFloat[2] = f3;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief VectorF3型の値をセットする
	//! @param [in] v VectorF3値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetVectorF3(const gt2Vector3 & v){
		if (m_type != __FLOAT3)return false;
		memcpy(_pFloat, v.v, sizeof(gt2Vector3));
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief 4つのfloat型の値をセットする
	//! @param [in] f1 値
	//! @param [in] f2 値
	//! @param [in] f3 値
	//! @param [in] f4 値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetFloat4(float f1, float f2, float f3, float f4){
		if (m_type != __FLOAT4)return false;
		_pFloat[0] = f1; _pFloat[1] = f2; _pFloat[2] = f3; _pFloat[3] = f4;
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief VectorF4型の値をセットする
	//! @param [in] v VectorF4値
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetVectorF4(const gt2Vector4 & v){
		if (m_type != __FLOAT4)return false;
		memcpy(_pFloat, v.v, sizeof(gt2Vector4));
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief float型の配列の値をセットする
	//! @param [in] pN    float型の配列ポインタ
	//! @param [in] count 配列のサイズ
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetFloatArray(const float *pN, gtUINT count){
		if (m_type != __ARY_FLOAT)return false;
		memcpy(_pFloat, pN, sizeof(float)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief int型の配列の値をセットする
	//! @param [in] pN    int型の配列ポインタ
	//! @param [in] count 配列のサイズ
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetIntArray(const int *pN, gtUINT count){
		if (m_type != __ARY_INT)return false;
		memcpy(_pInt, pN, sizeof(int)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief bool型の配列の値をセットする
	//! @param [in] pN    bool型の配列ポインタ
	//! @param [in] count 配列のサイズ
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetBoolArray(const bool *pN, gtUINT count){
		if (m_type != __ARY_BOOL)return false;
		memcpy(_pBool, pN, sizeof(bool)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief double型の配列の値をセットする
	//! @param [in] pN    double型の配列ポインタ
	//! @param [in] count 配列のサイズ
	//! @return 成功した場合trueを返す
	//-----------------------------------------------------------------------------------
	inline bool SetDoubleArray(const double *pN, gtUINT count){
		if (m_type != __ARY_DOUBLE)return false;
		memcpy(_pDouble, pN, sizeof(double)*count);
		return true;
	}
	//-----------------------------------------------------------------------------------
	//! @brief gt2Matrix4x4型の配列の値をセットする
	//! @param [in] pM    gt2Matrix4x4型の配列ポインタ
	//! @param [in] count 配列のサイズ
	//! @return 成功した場合trueを返す
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
//! @brief 複数の数値を作成するときに便利 @n
//!        構造体みたいな感じ
//-----------------------------------------------------------------------------------
class GT2UtilStructureValues
{
	friend class GT2UtilStructureValues;
	gt2UtiValues m_values;
public:
	//! デストラクタ
	virtual ~GT2UtilStructureValues() { }
	//-----------------------------------------------------------------------------------
	//! @brief GT2UtilStructureValues同士の代入演算子
	//! @param [in] r GT2UtilStructureValues
	//! @return GT2UtilStructureValues
	//-----------------------------------------------------------------------------------
	GT2UtilStructureValues& operator = (const GT2UtilStructureValues& r)
	{
		// 削除
		m_values.clear();
		m_values.insert(r.m_values.begin(), r.m_values.end());

		return *this;
	}
	//-----------------------------------------------------------------------------------
	//! @brief idx の順番通りの GT2UtilValue を作る
	//! @param [in] idx     インデックス値
	//! @param [in] type    型の種類
	//! @param [in] arySize 配列のサイズ。デフォルトで0(配列でない)
	//! @retval 成功した場合、0以上の層の値を返す。
	//! @retval 失敗した場合、-1を返す。
	//-----------------------------------------------------------------------------------
	inline bool Create(const int idx, gt2UtilValueType type, gtUINT arySize = 0)
	{
		if (m_values.find(idx) != m_values.end())return false;

		m_values.insert(gtMkPair(idx, GT2UtilValueSP(new GT2UtilValue())));

		return m_values[idx]->Create(type, arySize);
	}
	//-----------------------------------------------------------------------------------
	//! @brief 指定した層のGT2UtilValueSPを取得する。
	//! @param [in] idx    インデックス
	//! @retval 成功した場合、GT2UtilValueSPを返す
	//! @retval 失敗した場合、nullptrを返す。
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
	//! @brief 変数の数を返す
	//! @return 変数の数
	//-----------------------------------------------------------------------------------
	inline size_t Size() { return m_values.size(); }
	//-----------------------------------------------------------------------------------
	//! @brief この構造の変数全てを返す
	//! @return 変数全てを返す
	//-----------------------------------------------------------------------------------
	inline gt2UtiValues &GetValues() { return m_values; }
};
TYPEDEF_S_W_PTR(GT2UtilStructureValues);
