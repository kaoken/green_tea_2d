/*! @file  hresult.inl
* @brief MetalCube.hファイル内から呼び出されるので、ほかから呼び出さないように！
*  これは、短径を扱う構造体を使うためのもの
* @author kaoken
* @date 2014/03/19 作成開始
*/
#pragma once

//------------------------------------------------------------
//! @name windowsのHRESULTと互換性を持たせるために
//  以下のようにのHRESULT32ビット値がレイアウトされている
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//      S - Severity(重要度) - 成功/失敗を示している
//
//          0 - 成功
//          1 - 失敗 (COERROR)
//
//      R - ファシリティコードの予約部分は、NTの二番目にSeverityのビットに対応する。
//
//      C - ファシリティコードの予約部分は、NTのCフィールドに対応しています。
//
//      N - ファシリティコードの予約部分。マップされたNT状態値を示すために使用される。
//
//      r - ファシリティコードの予約部分。内部使用のために予約されています。
//          ステータス値ではありませんHRESULT値を示しているのではなく、表示文字列のメッセージIDのために使用します。
//
//      Facility - ファシリティコードです。
//
//      Code - ファシリティのステータスコードです
//------------------------------------------------------------
//@{
typedef long gt2HRESULT;
#define GT_HRESULT_TYPEDEF_(_sc) ((gt2HRESULT)_sc)
//!< 構成部品からHRESULT値を作成します。
#define GT_MAKE_HRESULT(sev,fac,code) ((gt2HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )
//!< 任意のステータス値による失敗のための一般的なテストを提供します。
#define GT_FAILED(hr) (((gt2HRESULT)(hr)) < 0)
//!< 任意のステータス値による成功のための一般的なテストを提供します。
#define GT_SUCCEEDED(hr) (((gt2HRESULT)(hr)) >= 0)
//!< ユーザー定義のエラーを作成
#define GT_MK_ERR_HRESULT(_no) GT_MAKE_HRESULT( 1, FACILITY_ITF, 0xF000+_no )

//***************
// エラーコード
//***************

//! エラーは発生していません。
#define GT_S_OK ((gt2HRESULT)0L)
//! 正常に処理されたものの、非標準の完了を示す代替成功値です (正確な意味はコンテキストによって異なります)。
#define GT_S_FALSE ((gt2HRESULT)1L)
//! 失敗した、予測できないエラーです。
#define GT_E_FAIL			GT_HRESULT_TYPEDEF_(0x80004005L)
//! 致命的なエラー
#define GT_E_UNEXPECTED		GT_HRESULT_TYPEDEF_(0x8000FFFFL)
//! アプリケーション定義またはオブジェクト定義のエラーです。
#define GT_E_ABORT			GT_HRESULT_TYPEDEF_(0x80004004L)
//! アクセスが拒否されました。
#define GT_E_ACCESSDENIED	GT_HRESULT_TYPEDEF_(0x80070005L)
//! ポインター値に誤って nullptr が渡されました。
#define GT_E_POINTER		GT_HRESULT_TYPEDEF_(0x80004003L)
//! 関数に無効なパラメーターが渡されました。
#define GT_E_INVALIDARG		GT_HRESULT_TYPEDEF_(0x80070057L)
//! アプリ呼び出しを完了するうえで十分なメモリーを割り当てることができませんでした。
#define GT_E_OUTOFMEMORY	GT_HRESULT_TYPEDEF_(0x8007000EL)
//! 特定の種類のステート オブジェクトの一意のインスタンスが多すぎます。
#define GT_E_TOO_MANY_UNIQUE_STATE_OBJECTS	GT_HRESULT_TYPEDEF_(0x887C0001L)
//! ファイルが見つかりませんでした。
#define GT_E_FILE_NOT_FOUND	GT_HRESULT_TYPEDEF_(0x887C0002L)
//! 特定の種類のビュー オブジェクトの一意のインスタンスが多すぎます。
#define GT_E_TOO_MANY_UNIQUE_VIEW_OBJECTS	GT_HRESULT_TYPEDEF_(0x887C0003L)
//! リソースごとの ID3D11Device::CreateDeferredContext の呼び出しまたは ID3D11DeviceContext::FinishCommandList の呼び出しの後で最初に呼び出した ID3D11DeviceContext::Map が D3D11_MAP_WRITE_DISCARD ではありませんでした。
#define GT_E_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD	GT_HRESULT_TYPEDEF_(0x887C0004L)
//! メソッドの呼び出しが無効です。たとえば、メソッドのパラメーターが有効なポインターでない可能性があります。
#define GT_E_INVALIDCALL	GT_MAKE_HRESULT( 1, 0x876, 2156 )
//! すでに作成済み
#define GT_E_CREATED		GT_MK_ERR_HRESULT(1)
//! 作成されていない
#define GT_E_NOT_CREATED	GT_MK_ERR_HRESULT(2)
//! 見つからなかった
#define GT_E_NOT_FIND		GT_MK_ERR_HRESULT(3)
//! 作成されていたが、型が違う種類だった
#define GT_E_CREATED_DIFFERENT_TYPE		GT_MK_ERR_HRESULT(4)
//! 登録失敗
#define GT_E_REGISTER_FAIL				GT_MK_ERR_HRESULT(5)
//! スクリプトで、実行が中断され、再開することができる。
#define GT_E_AS_EXECUTION_SUSPENDED		GT_MK_ERR_HRESULT(6)
//! スクリプトで、実行はアプリケーションによって中止されました。
#define GT_E_AS_EXECUTION_ABORTED		GT_MK_ERR_HRESULT(7)
//! スクリプトで、実行は、未処理のスクリプト例外によって終了した。
#define GT_E_AS_EXECUTION_EXCEPTION		GT_MK_ERR_HRESULT(8)
//! スクリプトで、コンテキストが、新しい実行のために準備されている。
#define GT_E_AS_EXECUTION_PREPARED		GT_MK_ERR_HRESULT(9)
//! スクリプトで、コンテキストが初期化されていません。
#define GT_E_AS_EXECUTION_UNINITIALIZED	GT_MK_ERR_HRESULT(10)
//! スクリプトで、コンテキストが、現在の関数呼び出しを実行している。
#define GT_E_AS_EXECUTION_ACTIVE		GT_MK_ERR_HRESULT(11)
//! スクリプトで、コンテキストが、エラーが発生したため、再初期化する必要があります。
#define GT_E_AS_EXECUTION_ERROR			GT_MK_ERR_HRESULT(12)
//@}
