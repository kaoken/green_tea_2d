#include "../greenTea2D.h"
#include <unicode/utypes.h>
#include <unicode/uclean.h>
#include <unicode/ucnv.h>
#include <unicode/umachine.h>
#include <string.h>


/** 作成されたメモリーのチェック
 * 
 */

#define CNV_MEM_CHECK(_funcName, _pp) \
	if (*_pp == nullptr) { \
		Trace(_funcName, ICU_ErrorString(U_MEMORY_ALLOCATION_ERROR)); \
		ret = false; \
		goto UCNV_END; \
	}


/*!
* @brief ICU用のエラー文字列取得関数
* @param [in]  error  エラーの種類
* @return エラー文字列を返す
*/
static const TChar* ICU_ErrorString(const UErrorCode error)
{
	switch (error)
	{
	case U_USING_FALLBACK_WARNING: return _T("リソースバンドルの検索は、フォールバックの結果（エラーではない）を返しました");
		//		case U_ERROR_WARNING_START: return _T("情報結果（意味的に成功した）の開始");
	case U_USING_DEFAULT_WARNING: return _T("リソースバンドル検索はルートロケール（エラーではない）の結果を返しました");
	case U_SAFECLONE_ALLOCATED_WARNING: return _T("SafeClone操作はメモリ（情報のみ）を割り当てる必要がありました");
	case U_STATE_OLD_WARNING: return _T("ICUは、サービスを構成するために、互換性レイヤを使用しなければならない。\nパフォーマンス/メモリ使用量の低下を期待し、アップグレードを検討してください");
	case U_STRING_NOT_TERMINATED_WARNING: return _T("出力文字列があるため \"出力の長さ==destCapacity\" nullptrで終了することができませんでした");
	case U_SORT_KEY_TOO_SHORT_WARNING: return _T("getBoundで要求されたレベルの数は、ソートキーのレベル数よりも高くなっています");
	case U_AMBIGUOUS_ALIAS_WARNING: return _T("このコンバータの別名は異なるコンバータの実装に行くことができます");
	case U_DIFFERENT_UCA_VERSION: return _T("ucol_openはUCAバージョンと照合イメージのバージョンの間に不一致が発生したので、照合は、ルールから構築された。\n更に関数への影響はありません。");
	case U_PLUGIN_CHANGED_LEVEL_WARNING: return _T("プラグインは、レベルの変化を引き起こした。\nエラーではないかもしれないが、後にプラグインが読み込まれないことがあります。");
	case U_ERROR_WARNING_LIMIT: return _T("これは、常にUErrorCodeの警告（最後の警告コード+1）の制限を示すために最後の警告値でなければなりません。");
	case U_ZERO_ERROR: return _T("エラーなし、警告なし。");
	case U_ILLEGAL_ARGUMENT_ERROR: return _T("失敗を示すコードの開始");
	case U_MISSING_RESOURCE_ERROR: return _T("要求されたリソースが見つかりません");
	case U_INVALID_FORMAT_ERROR: return _T("データフォーマットが期待されないもの。");
	case U_FILE_ACCESS_ERROR: return _T("要求されたファイルが見つかりません。");
	case U_INTERNAL_PROGRAM_ERROR: return _T("ライブラリのコードにバグがあることを示します。");
	case U_MESSAGE_PARSE_ERROR: return _T("メッセージ（メッセージ・フォーマット）を解析することができません。");
	case U_MEMORY_ALLOCATION_ERROR: return _T("メモリ割り当てエラー");
	case U_INDEX_OUTOFBOUNDS_ERROR: return _T("範囲外のインデックスにアクセスしようとしています");
	case U_PARSE_ERROR: return _T("JavaのParseExceptionがに相当");
	case U_INVALID_CHAR_FOUND: return _T("文字変換：マッピング不能入力シーケンス。\n他のAPIの場合：無効な文字。");
	case U_TRUNCATED_CHAR_FOUND: return _T("文字変換：不完全な入力シーケンス。");
	case U_ILLEGAL_CHAR_FOUND: return _T("文字変換：不正入力シーケンス/入力ユニットの組み合わせ。");
	case U_INVALID_TABLE_FORMAT: return _T("変換テーブルファイルが見つかりましたが、破損した。");
	case U_INVALID_TABLE_FILE: return _T("変換テーブルファイルが見つかりません。");
	case U_BUFFER_OVERFLOW_ERROR: return _T("結果は、指定されたバッファに収まらないだろう。");
	case U_UNSUPPORTED_ERROR: return _T("要求された操作は、現在のコンテキストではサポートされません。");
	case U_RESOURCE_TYPE_MISMATCH: return _T("操作は、それをサポートしていないリソースを介して要求される。");
	case U_ILLEGAL_ESCAPE_SEQUENCE: return _T("不正なISO-2022エスケープシーケンス。");
	case U_UNSUPPORTED_ESCAPE_SEQUENCE: return _T("サポートされていないISO-2022エスケープシーケンス。");
	case U_NO_SPACE_AVAILABLE: return _T("整形アラビア語のためにバッファ拡張のための利用可能なスペースがありません。");
	case U_CE_NOT_FOUND_ERROR: return _T("現在使用されている専用変数トップを設定するが、一般的に使用できた。");
	case U_PRIMARY_TOO_LONG_ERROR: return _T("ユーザーが2バイトより長い主な変数トップを設定しようとしました。");
	case U_STATE_TOO_OLD_ERROR: return _T("ICUは、この状態からサービスを構築することができないものとして、それはもはやサポートされていません。");
	case U_TOO_MANY_ALIASES_ERROR: return _T("あまりにも多くのエイリアスが要求されたリソースへのパスがある。\nこれは、円形の別名定義が発生した可能性が非常にあります。");
	case U_ENUM_OUT_OF_SYNC_ERROR: return _T("基になるコレクションと同期のUEnumerationアウト。");
	case U_INVARIANT_CONVERSION_ERROR: return _T("不変コンバータとchar *にUCHAR*文字列を変換できません。");
	case U_INVALID_STATE_ERROR: return _T("要求された操作は、現在の状態でICUで完了することができません。");
	case U_COLLATOR_VERSION_MISMATCH: return _T("照合バージョンは、ベースバージョンと互換性がありません。");
	case U_USELESS_COLLATOR_ERROR: return _T("照合はオプションだけで、全くベースが指定されていません。");
	case U_NO_WRITE_PERMISSION: return _T("読み取り専用または定数データを変更しよう。");
	case U_STANDARD_ERROR_LIMIT: return _T("これは常に標準誤差の限界を示すために最後の値でなければなりません。");
	case U_BAD_VARIABLE_DEFINITION: return _T("'$'がみつからないまたは変数名が重複。");
		//		case U_PARSE_ERROR_START: return _T("Transliteratorエラーの開始。");
	case U_MALFORMED_RULE: return _T("ルールの要素がみつからない。");
	case U_MALFORMED_SET: return _T("UnicodeSetパターンが無効です。");
	case U_MALFORMED_SYMBOL_REFERENCE: return _T("CU2.4としてUNUSED。");
	case U_MALFORMED_UNICODE_ESCAPE: return _T("Unicodeエスケープパターンが無効です。");
	case U_MALFORMED_VARIABLE_DEFINITION: return _T("変数定義が無効です。");
	case U_MALFORMED_VARIABLE_REFERENCE: return _T("変数参照が無効です。");
	case U_MISMATCHED_SEGMENT_DELIMITERS: return _T("CU2.4としてUNUSED。");
	case U_MISPLACED_ANCHOR_START: return _T("開始アンカーは不正位置で表示されます。");
	case U_MISPLACED_CURSOR_OFFSET: return _T("オフセットはカーソルが不正位置で発生する。");
	case U_MISPLACED_QUANTIFIER: return _T("修飾子は、セグメントに近い区切り記号の後に表示されます。");
	case U_MISSING_OPERATOR: return _T("ルールがない演算子が含まれていません。");
	case U_MISSING_SEGMENT_CLOSE: return _T("CU2.4としてUNUSED。");
	case U_MULTIPLE_ANTE_CONTEXTS: return _T("複数事前コンテキスト。");
	case U_MULTIPLE_CURSORS: return _T("1つのカーソルより。");
	case U_MULTIPLE_POST_CONTEXTS: return _T("複数のポストコンテキスト。");
	case U_TRAILING_BACKSLASH: return _T("ダングリングバックスラッシュ。");
	case U_UNDEFINED_SEGMENT_REFERENCE: return _T("セグメントの参照は、定義されたセグメントに対応していません。");
	case U_UNDEFINED_VARIABLE: return _T("変数の参照は、定義された変数に対応していません。");
	case U_UNQUOTED_SPECIAL: return _T("特殊文字は、クォートまたはエスケープがされていませんでした。");
	case U_UNTERMINATED_QUOTE: return _T("閉じるシングルクォートが欠落しています。");
	case U_RULE_MASK_ERROR: return _T("ルールは以前より一般的な規則によって隠されています。");
	case U_MISPLACED_COMPOUND_FILTER: return _T("複合フィルタが無効な位置にあります。");
	case U_MULTIPLE_COMPOUND_FILTERS: return _T("複数の複合フィルター。");
	case U_INVALID_RBT_SYNTAX: return _T("\"::id\"ルールはRuleBasedTransliteratorパーサーに渡されました。");
	case U_INVALID_PROPERTY_PATTERN: return _T("CU2.4としてUNUSED。");
	case U_MALFORMED_PRAGMA: return _T("'use'プラグマは無効です。");
	case U_UNCLOSED_SEGMENT: return _T("閉じる')'がみつからない。");
	case U_ILLEGAL_CHAR_IN_SEGMENT: return _T("CU2.4としてUNUSED。");
	case U_VARIABLE_RANGE_EXHAUSTED: return _T("あまりにも多く、スタンドインを与えられた変数の範囲のために生成。");
	case U_VARIABLE_RANGE_OVERLAP: return _T("ルールで使用される変数の範囲と重なる文字。");
	case U_ILLEGAL_CHARACTER: return _T("特殊文字は許可されたコンテキストの外にある。");
	case U_INTERNAL_TRANSLITERATOR_ERROR: return _T("内部transliteratorシステムエラー。");
	case U_INVALID_ID: return _T("\"::id\"は、ルールが不明のtransliteratorを指定します。");
	case U_INVALID_FUNCTION: return _T("\"&fn()\"は、ルールが不明のtransliteratorを指定します。");
	case U_PARSE_ERROR_LIMIT: return _T("Transliteratorエラーの限界。");
	case U_UNEXPECTED_TOKEN: return _T("フォーマットパターンに構文エラーがあります。");
		//		case U_FMT_PARSE_ERROR_START: return _T("フォーマット・ライブラリエラーの開始。");
	case U_MULTIPLE_DECIMAL_SEPARATORS: return _T("番号のパターンに複数の小数点記号。");
		//		case U_MULTIPLE_DECIMAL_SEPERATORS: return _T("誤字：後方互換性のために保持。\nU_MULTIPLE_DECIMAL_SEPARATORSを使用。");
	case U_MULTIPLE_EXPONENTIAL_SYMBOLS: return _T("番号のパターンに複数の指数記号。");
	case U_MALFORMED_EXPONENTIAL_PATTERN: return _T("指数パターンでシンボルをグループ化する。");
	case U_MULTIPLE_PERCENT_SYMBOLS: return _T("番号のパターンで複数のパーセント記号。");
	case U_MULTIPLE_PERMILL_SYMBOLS: return _T("番号のパターンで複数のパーミル記号。");
	case U_MULTIPLE_PAD_SPECIFIERS: return _T("番号のパターンで複数のパッドシンボル。");
	case U_PATTERN_SYNTAX_ERROR: return _T("フォーマットパターンに構文エラーがあります。");
	case U_ILLEGAL_PAD_POSITION: return _T("パッド記号は番号パターンで紛失し。");
	case U_UNMATCHED_BRACES: return _T("中括弧は、メッセージパターンに一致していません。");
	case U_UNSUPPORTED_PROPERTY: return _T("ICU2.4としてUNUSED。");
	case U_UNSUPPORTED_ATTRIBUTE: return _T("ICU2.4としてUNUSED。");
	case U_ARGUMENT_TYPE_MISMATCH: return _T("MessageFormatの関数の引数名と引数インデックスの不一致。");
	case U_DUPLICATE_KEYWORD: return _T("複数形のキーワードを複製します。");
	case U_UNDEFINED_KEYWORD: return _T("未定義・複数のキーワード。");
	case U_DEFAULT_KEYWORD_MISSING: return _T("複数のルールでデフォルトルールがありません。");
	case U_DECIMAL_NUMBER_SYNTAX_ERROR: return _T("10数の構文エラー。");
	case U_FORMAT_INEXACT_ERROR: return _T("正確に数値をフォーマットして丸め誤差モードは、ROUND_UNNECESSARYであることはできません。安定：ICU4.8");
	case U_FMT_PARSE_ERROR_LIMIT: return _T("フォーマット・ライブラリのエラーの限界。");
	case U_BRK_INTERNAL_ERROR: return _T("内部エラー（バグ）が検出されました。");
		//		case U_BRK_ERROR_START: return _T("ブレークイテレータの失敗を示すコードの開始。");
	case U_BRK_HEX_DIGITS_EXPECTED: return _T("16進数は、ルールでエスケープされchar型の一部として期待。");
	case U_BRK_SEMICOLON_EXPECTED: return _T("RBBIルールの終わりに';'がみつからない。");
	case U_BRK_RULE_SYNTAX: return _T("RBBIルールに構文エラーがあります。");
	case U_BRK_UNCLOSED_SET: return _T("クロージング']'が不足しているRBBIルールを書いてUnicodeSet。");
	case U_BRK_ASSIGN_ERROR: return _T("RBBIルール代入文に構文エラーがあります。");
	case U_BRK_VARIABLE_REDFINITION: return _T("RBBIルール$変数が再定義。");
	case U_BRK_MISMATCHED_PAREN: return _T("Mis-matched parentheses in an RBBI rule");
	case U_BRK_NEW_LINE_IN_QUOTED_STRING: return _T("RBBIルールで閉じる引用符がありません。");
	case U_BRK_UNDEFINED_VARIABLE: return _T("RBBIルールで定義されていない$変数を使用。");
	case U_BRK_INIT_ERROR: return _T("初期化に失敗。考えられるICUデータの不足している。");
	case U_BRK_RULE_EMPTY_SET: return _T("ルールは空のUnicodeのセットが含まれています。");
	case U_BRK_UNRECOGNIZED_OPTION: return _T("!!認識されないRBBIルール内のオプション。");
	case U_BRK_MALFORMED_RULE_TAG: return _T("ルール上の{nnn}タグの形式が正しくありません。");
	case U_BRK_ERROR_LIMIT: return _T("これは、常にブレークイテレータの失敗の制限を示すために最後の値でなければなりません。");
	case U_REGEX_INTERNAL_ERROR: return _T("内部エラー（バグ）が検出されました。");
		//		case U_REGEX_ERROR_START: return _T("Regexpの障害を示すコードの開始。");
	case U_REGEX_RULE_SYNTAX: return _T("正規表現パターンの構文エラー。");
	case U_REGEX_INVALID_STATE: return _T("要求された操作のため無効な状態でRegexMatcher。");
	case U_REGEX_BAD_ESCAPE_SEQUENCE: return _T("パターンで認識されていないバックスラッシュエスケープシーケンス。");
	case U_REGEX_PROPERTY_SYNTAX: return _T("不正なUnicodeのプロパティです。");
	case U_REGEX_UNIMPLEMENTED: return _T("まだ実装されていませんregexp関数の使用。");
	case U_REGEX_MISMATCHED_PAREN: return _T("誤って正規表現パターンで括弧がネストされた。");
	case U_REGEX_NUMBER_TOO_BIG: return _T("10進数が大きすぎる。");
	case U_REGEX_BAD_INTERVAL: return _T("{min、max}間隔中にエラーが発生しました。");
	case U_REGEX_MAX_LT_MIN: return _T("{min、max}で、maxはminより小さい。");
	case U_REGEX_INVALID_BACK_REF: return _T("存在しないキャプチャグループへの後方参照。");
	case U_REGEX_INVALID_FLAG: return _T("マッチモードフラグの値が無効です。");
	case U_REGEX_LOOK_BEHIND_LIMIT: return _T("ルックビハインドパターンマッチは、有界最大長を持っている必要があります。");
	case U_REGEX_SET_CONTAINS_STRING: return _T("正規表現は、文字列を含むUnicodeSetsを持つことはできません。");
	case U_REGEX_OCTAL_TOO_BIG: return _T("8進数文字定数は、<=0377である必要があります。");
	case U_REGEX_MISSING_CLOSE_BRACKET: return _T("括弧式に閉じ括弧がありません。");
	case U_REGEX_INVALID_RANGE: return _T("文字範囲において[x-y]、xはyよりも大きい。");
	case U_REGEX_STACK_OVERFLOW: return _T("正規表現バックトラックスタックオーバーフロー。");
	case U_REGEX_TIME_OUT: return _T("最大許容一致時間が超過しました。");
	case U_REGEX_STOPPED_BY_CALLER: return _T("マッチング操作は、ユーザコールバックFNによって中止。");
	case U_REGEX_ERROR_LIMIT: return _T("これは、常に正規表現エラーの限界を示すために最後の値でなければなりません。");
		//		case U_PLUGIN_ERROR_START: return _T("プラグインの障害を示すコードの開始。");
	case U_PLUGIN_TOO_HIGH: return _T("プラグインのレベルは今ロードするには高すぎる。");
	case U_PLUGIN_DIDNT_SET_LEVEL: return _T("プラグインは、クエリーに応じてuplug_setPlugLevelを呼び出さなかった。");
	case U_PLUGIN_ERROR_LIMIT: return _T("これは、常にプラグインエラーの限界を示すために最後の値でなければなりません。");
		//		case U_ERROR_LIMIT 	: return _T("これは常にUErrorCode（最後のエラーコード+1）の制限を示すために最後の値でなければなりません。");
	}
	return _T("");
}

static const char* g_ConvertFormat[] = {
	"shift_jis",
	"utf-8",
	"utf-16",
	"utf-16b",
};

//bool MCStringConvert(
//	KN_CONVERT_FORMAT src,
//	KN_CONVERT_FORMAT dest,
//	const std::string &strSrc,
//	std::string *pOut)
//{
//	UTIL_RECUTSIVE_LOCK();

//	UConverter *pCnvSrc = nullptr, *pCnvDest = nullptr;
//	UErrorCode error = U_ZERO_ERROR;
//	size_t lenSrc, lenDest;
//	const char *pTmpSrc;
//	char *pTmpDest, **ppBffDest = nullptr;
//	bool ret = true;

//	if (strSrc.empty())
//		return false;

//	u_init(&error);

//	pCnvSrc = ucnv_open(g_ConvertFormat[src], &error);
//	if (U_FAILURE(error)) {
//		Trace(_T("MCStringConvert(%d,%d) First argument error:%s"), src, dest, ICU_ErrorString(error));
//		ret = false;
//		goto UCNV_END;
//	}
//	lenSrc = strSrc.length();

//	pCnvDest = ucnv_open(g_ConvertFormat[dest], &error);
//	if (U_FAILURE(error)) {
//		Trace(_T("MCStringConvert(%d,%d) Second argument error:%s"), src, dest, ICU_ErrorString(error));
//		ret = false;
//		goto UCNV_END;
//	}

//	if (lenSrc < 256)
//		lenDest = 256;
//	else
//		lenDest = lenSrc << 1;


//	do
//	{
//		*ppBffDest = new char[lenDest]; // 出力領域の確保
//		if (*ppBffDest == nullptr) {
//			Trace(_T("MCStringConvert(%d,%d) error:%s"), src, dest, ICU_ErrorString(error));
//			ret = false;
//			goto UCNV_END;
//		}
//		memset(*ppBffDest, 0, lenDest);

//		pTmpSrc = strSrc.c_str();
//		pTmpDest = *ppBffDest;

//		ucnv_convertEx(pCnvDest, pCnvSrc,
//			&pTmpDest, pTmpDest + lenDest,
//			&pTmpSrc, pTmpSrc + lenSrc,
//			nullptr, nullptr, nullptr, nullptr, 1, 1, &error);
//		if (U_FAILURE(error))
//		{
//			SAFE_DELETE_ARRAY(*ppBffDest);
//			if (error == U_BUFFER_OVERFLOW_ERROR)
//			{
//				lenDest <<= 1;
//				error = U_ZERO_ERROR;
//			}
//			else
//			{
//				Trace(_T("MCStringConvert(%d,%d) error:%s"), src, dest, ICU_ErrorString(error));
//				ret = false;
//				goto UCNV_END;
//			}
//		}
//		else
//			break;
//	} while (true);

//UCNV_END:
//	ucnv_close(pCnvDest);
//	ucnv_close(pCnvSrc);
//	u_cleanup();
//	return ret;
//}


//###################################################################
//###################################################################
//###
//### ShiftJIS -----> xxxx
//###
//###################################################################
//###################################################################

static bool Convert_SJIS_To_UTF8(const char *pSjis, char **ppUTF8)
{
	UTIL_RECUTSIVE_LOCK();

	UConverter *pCnvSJIS = nullptr, *pCnvUTF8 = nullptr;
	UErrorCode error = U_ZERO_ERROR;
	size_t lenSJIS, lenUTF8;
	const char *pTmpSJIS;
	char *pTmpUTF8;
	bool ret = true;

	u_init(&error);

	pCnvSJIS = ucnv_open("shift_jis", &error);
	if (U_FAILURE(error)) {
		Trace(_T("Convert_SJIS_To_UTF8() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}

	pCnvUTF8 = ucnv_open("utf-8", &error);
	if (U_FAILURE(error)) {
		Trace(_T("Convert_SJIS_To_UTF8() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}

	lenSJIS = strlen(pSjis) + 1;
	lenUTF8 = lenSJIS / ucnv_getMinCharSize(pCnvSJIS) * ucnv_getMaxCharSize(pCnvUTF8) + 1;


	do
	{
		*ppUTF8 = new char[lenUTF8]; // 出力領域の確保
		CNV_MEM_CHECK(_T("Convert_SJIS_To_UTF8() error:%s"), ppUTF8);
		memset(*ppUTF8, 0, lenUTF8);

		pTmpSJIS = pSjis;
		pTmpUTF8 = *ppUTF8;

		ucnv_convertEx(pCnvUTF8, pCnvSJIS,
			&pTmpUTF8, pTmpUTF8 + lenUTF8,
			&pTmpSJIS, pTmpSJIS + lenSJIS,
			nullptr, nullptr, nullptr, nullptr, 1, 1, &error);
		if (U_FAILURE(error))
		{
			SAFE_DELETE_ARRAY(*ppUTF8);
			if (error == U_BUFFER_OVERFLOW_ERROR)
			{
				lenUTF8 <<= 1;
				error = U_ZERO_ERROR;
			}
			else
			{
				Trace(_T("Convert_SJIS_To_UTF8() error:%s"), ICU_ErrorString(error));
				ret = false;
				goto UCNV_END;
			}
		}
		else
			break;
	} while (true);

UCNV_END:
	ucnv_close(pCnvUTF8);
	ucnv_close(pCnvSJIS);
	u_cleanup();
	return ret;
}

bool Convert_SJIS_To_UTF8(const std::string& src, stringU8 *pUTF8)
{
	char* pBff = nullptr;
	if (Convert_SJIS_To_UTF8(src.c_str(), &pBff))
	{
		*pUTF8 = pBff;
		SAFE_DELETE_ARRAY(pBff);
		return true;
	}
	return false;
}

static bool Convert_SJIS_To_UTF16(const char* pSrc, UChar** ppOut)
{
	UTIL_RECUTSIVE_LOCK();

	UErrorCode error = U_ZERO_ERROR;
	size_t      sourceLength = 0;		// 入力の長さ(バイト数)
	bool ret = true;
	*ppOut = nullptr;

	UConverter* pConv = ucnv_open("sjis", &error); // UConverterの生成
	if (U_FAILURE(error)) {
		Trace(_T("Convert_SJIS_To_UTF16() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = strlen(pSrc) + 1;

	do
	{
		*ppOut = new UChar[sourceLength]; // 出力領域の確保
		CNV_MEM_CHECK(_T("Convert_SJIS_To_UTF16() error:%s"), ppOut);
		memset(*ppOut, 0, sourceLength);
		UChar* pPos = *ppOut;
		const char* pIn = pSrc;

		// マルチバイト文字列(shift_jis) から Unicode へ変換
		// void ucnv_toUnicode_59(UConverter *,UChar **,const UChar *,const char **,const char *,int32_t *,UBool,UErrorCode *)
		ucnv_toUnicode(
			pConv,					// Unicodeコンバータ
			&pPos,					// 出力バッファの先頭
			pPos + sourceLength,	// 出力バッファの上限
			&pIn,					// 入力バッファの先頭
			pIn + sourceLength,		// 入力バッファの上限
			0,						// 常に0
			TRUE,					// 入力シーケンスの終端であればTRUE
			&error					// エラーコード
			);
		if (U_FAILURE(error))
		{
			SAFE_DELETE_ARRAY(*ppOut);
			if (error == U_BUFFER_OVERFLOW_ERROR)
			{
				sourceLength <<= 1;
				error = U_ZERO_ERROR;
			}
			else
			{
				Trace(_T("Convert_SJIS_To_UTF16() error:%s"), ICU_ErrorString(error));
				ret = false;
				goto UCNV_END;
			}
		}
		else
			break;
	} while (true);
UCNV_END:
	ucnv_close(pConv); // UConverterの開放
	u_cleanup();
	return ret;
}

bool Convert_SJIS_To_UTF16(const std::string& src, std::wstring* pOut)
{
	UChar* pBff;

	if (!Convert_SJIS_To_UTF16(src.c_str(), &pBff))
		return false;
	*pOut = (wchar_t*)pBff;
	SAFE_DELETE_ARRAY(pBff);
	return true;
}

bool Convert_SJIS_To_TCHAR(const std::string &src, TString *pOut)
{
#ifdef _UNICODE
	return Convert_SJIS_To_UTF16(src, pOut);
#else
	*pOut = src;
	return true;
#endif
}


//###################################################################
//###################################################################
//###
//### UTF8 -----> xxxx
//###
//###################################################################
//###################################################################

static bool Convert_UTF8_To_SJIS(const char *pUTF8, char **ppSjis)
{
	UTIL_RECUTSIVE_LOCK();

	UConverter *pCnvSJIS = nullptr, *pCnvUTF8 = nullptr;
	UErrorCode error = U_ZERO_ERROR;
	size_t lenSJIS, lenUTF8;
	const char *pTmpUTF8;
	char *pTmpSJIS;
	bool ret = true;

	u_init(&error);

	pCnvUTF8 = ucnv_open("utf-8", &error);
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF8_To_SJIS() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}

	pCnvSJIS = ucnv_open("shift_jis", &error);
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF8_To_SJIS() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}

	lenUTF8 = strlen(pUTF8) + 1;

	lenSJIS = lenUTF8 * ucnv_getMinCharSize(pCnvSJIS) / ucnv_getMaxCharSize(pCnvUTF8) + 1;

	do
	{
		*ppSjis = new char[lenSJIS]; // 出力領域の確保
		CNV_MEM_CHECK(_T("Convert_UTF8_To_SJIS() error:%s"), ppSjis);
		memset(*ppSjis, 0, lenSJIS);

		pTmpUTF8 = pUTF8;
		pTmpSJIS = *ppSjis;

		ucnv_convertEx(pCnvUTF8, pCnvSJIS,
			&pTmpSJIS, pTmpSJIS + lenSJIS,
			&pTmpUTF8, pTmpUTF8 + lenUTF8,
			nullptr, nullptr, nullptr, nullptr, 1, 1, &error);
		if (U_FAILURE(error))
		{
			SAFE_DELETE_ARRAY(*ppSjis);
			if (error == U_BUFFER_OVERFLOW_ERROR)
			{
				lenSJIS <<= 1;
				error = U_ZERO_ERROR;
			}
			else
			{
				Trace(_T("Convert_UTF8_To_SJIS() error:%s"), ICU_ErrorString(error));
				ret = false;
				goto UCNV_END;
			}
		}
		else
			break;
	} while (true);

UCNV_END:
	ucnv_close(pCnvUTF8);
	ucnv_close(pCnvSJIS);
	u_cleanup();
	return ret;
}

bool Convert_UTF8_To_SJIS(const stringU8 &src, std::string *pSjis)
{
	char* pBff = nullptr;
	if (Convert_UTF8_To_SJIS(src.c_str(), &pBff))
	{
		*pSjis = pBff;
		SAFE_DELETE_ARRAY(pBff);
		return true;
	}
	return false;
}

static bool Convert_UTF8_To_UTF16(const char *pUTF8, UChar **ppUTF16)
{
	UTIL_RECUTSIVE_LOCK();

	UErrorCode error = U_ZERO_ERROR;
	size_t      sourceLength = 0;		// 入力の長さ(バイト数)
	bool ret = true;
	*ppUTF16 = nullptr;

	UConverter* pConv = ucnv_open("utf-8", &error); // UConverterの生成
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF8_To_UTF16() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = strlen(pUTF8) + 1;


	do
	{
		*ppUTF16 = new UChar[sourceLength]; // 出力領域の確保
		CNV_MEM_CHECK(_T("Convert_UTF8_To_UTF16() error:%s"), ppUTF16);
		memset(*ppUTF16, 0, sizeof(UChar)*sourceLength);

		UChar* pPos = *ppUTF16;
		const char* pIn = pUTF8;

		// マルチバイト文字列(shift_jis) から Unicode へ変換
		ucnv_toUnicode(
			pConv,					// Unicodeコンバータ
			&pPos,					// 出力バッファの先頭
			pPos + sourceLength,	// 出力バッファの上限
			&pIn,					// 入力バッファの先頭
			pIn + sourceLength,		// 入力バッファの上限
			0,						// 常に0
			TRUE,					// 入力シーケンスの終端であればTRUE
			&error					// エラーコード
			);
		if (U_FAILURE(error)) {
			SAFE_DELETE_ARRAY(*ppUTF16);
			if (error == U_BUFFER_OVERFLOW_ERROR)
			{
				sourceLength <<= 1;
				error = U_ZERO_ERROR;
			}
			else
			{
				Trace(_T("Convert_UTF8_To_UTF16() error:%s"), ICU_ErrorString(error));
				ret = false;
				goto UCNV_END;
			}
		}
		else
			break;
	} while (true);
UCNV_END:
	ucnv_close(pConv); // UConverterの開放
	u_cleanup();
	return ret;
}

bool Convert_UTF8_To_UTF16(const stringU8& src, std::wstring *pUTF16)
{
	UChar* pBff = nullptr;
	if (Convert_UTF8_To_UTF16(src.c_str(), &pBff))
	{
		*pUTF16 = (wchar_t*)pBff;
		SAFE_DELETE_ARRAY(pBff);
		return true;
	}
	return false;
}

bool Convert_UTF8_To_TCHAR(const stringU8& src, TString *pOut)
{
#ifdef _UNICODE
	return Convert_UTF8_To_UTF16(src, pOut);
#else
	return Convert_UTF8_To_SJIS(src, pOut);
#endif
}




//###################################################################
//###################################################################
//###
//### UTF16 -----> xxxx
//###
//###################################################################
//###################################################################

//===================================================================
// Convert_UTF16_To_SJIS
//===================================================================

static bool Convert_UTF16_To_SJIS(const UChar* pSrc, char** ppOut)
{
	UTIL_RECUTSIVE_LOCK();

	UErrorCode error = U_ZERO_ERROR;
	size_t      sourceLength = 0;	// 入力の長さ(バイト数)
	size_t      outLength = 0;		// 出力の長さ(バイト数)
	bool ret = true;
	*ppOut = nullptr;

	u_init(&error);

	UConverter* pConv = ucnv_open("sjis", &error); // UConverterの生成
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF16_To_SJIS() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = wcslen((wchar_t*)pSrc);
	outLength = sourceLength * 2 + 1;


	do{
		*ppOut = new char[outLength]; // 出力領域の確保
		CNV_MEM_CHECK(_T("Convert_UTF16_To_SJIS() error:%s"), ppOut);
		memset(*ppOut, 0, outLength);

		char* pPos = *ppOut;
		const UChar* pIn = pSrc;

		// Unicode から マルチバイト文字列(shift_jis) へ変換
		ucnv_fromUnicode(
			pConv,					// Unicodeコンバータ
			&pPos,					// 出力バッファの先頭
			pPos + outLength,		// 出力バッファの上限
			&pIn,					// 入力バッファの先頭
			pIn + sourceLength,		// 入力バッファの上限
			0,						// 常に0
			TRUE,					// 入力シーケンスの終端であればTRUE
			&error					// エラーコード
			);
		if (U_FAILURE(error)) {
			// バッファサイズが小さいので大きく作り直す
			SAFE_DELETE_ARRAY(*ppOut);
			if (error == U_BUFFER_OVERFLOW_ERROR)
			{
				outLength = outLength << 1;
				error = U_ZERO_ERROR;
			}
			else
			{
				Trace(_T("Convert_UTF16_To_SJIS() error:%s"), ICU_ErrorString(error));
				ret = false;
				goto UCNV_END;
			}
		}
		else
			break;
	} while (true);
UCNV_END:
	ucnv_close(pConv); // UConverterの開放
	u_cleanup();
	return ret;
}

bool Convert_UTF16_To_SJIS(const std::wstring& src, std::string* pOut)
{
	char* pBff;

	if (!Convert_UTF16_To_SJIS((UChar*)src.c_str(), &pBff))
		return false;
	*pOut = pBff;
	SAFE_DELETE_ARRAY(pBff);
	return true;
}



//===================================================================
// Convert_UTF16_To_UTF8
//===================================================================
static bool Convert_UTF16_To_UTF8(const UChar* pSrc, char** ppOut)
{
	UTIL_RECUTSIVE_LOCK();

	UErrorCode error = U_ZERO_ERROR;
	size_t      sourceLength = 0;	// 入力の長さ(バイト数)
	size_t      outLength = 0;		// 出力の長さ(バイト数)
	bool ret = true;
	*ppOut = nullptr;

	u_init(&error);

	UConverter* pConv = ucnv_open("utf-8", &error); // UConverterの生成
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF16_To_UTF8() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = wcslen((wchar_t*)pSrc);
	outLength = sourceLength * 2 + 1;

	do{

		*ppOut = new char[outLength]; // 出力領域の確保
		CNV_MEM_CHECK(_T("Convert_UTF16_To_UTF8() error:%s"), ppOut);
		memset(*ppOut, 0, outLength);

		char* pPos = *ppOut;
		const UChar* pIn = pSrc;

		// Unicode から マルチバイト文字列(shift_jis) へ変換
		ucnv_fromUnicode(
			pConv,					// Unicodeコンバータ
			&pPos,					// 出力バッファの先頭
			pPos + outLength,		// 出力バッファの上限
			&pIn,					// 入力バッファの先頭
			pIn + sourceLength,		// 入力バッファの上限
			0,						// 常に0
			TRUE,					// 入力シーケンスの終端であればTRUE
			&error					// エラーコード
			);
		if (U_FAILURE(error)) {
			SAFE_DELETE_ARRAY(*ppOut);
			if (error == U_BUFFER_OVERFLOW_ERROR)
			{
				// バッファサイズが小さいので大きく作り直す
				outLength = outLength << 1;
				error = U_ZERO_ERROR;
			}
			else
			{
				Trace(_T("Convert_UTF16_To_UTF8() error:%s"), ICU_ErrorString(error));
				ret = false;
				goto UCNV_END;
			}
		}
		else
			break;
	} while (true);
UCNV_END:
	ucnv_close(pConv); // UConverterの開放
	u_cleanup();
	return ret;
}

bool Convert_UTF16_To_UTF8(const std::wstring &src, std::string* pOut)
{
	char* pBff;

	if (!Convert_UTF16_To_UTF8((UChar*)src.c_str(), &pBff))
		return false;
	*pOut = pBff;
	SAFE_DELETE_ARRAY(pBff);
	return true;
}





//===================================================================
// Convert_TCHAR_To_SJIS
//===================================================================


bool Convert_TCHAR_To_SJIS(const TString& src, std::string* pOut)
{
#ifdef _UNICODE
	if (!Convert_UTF16_To_SJIS(src.c_str(), pOut))
		return false;
#else
	*pOut = src;
#endif
	return true;
}

bool Convert_TCHAR_To_UTF8(const TString& src, stringU8* pOut)
{
#ifdef _UNICODE
	return Convert_UTF16_To_UTF8(src, pOut);
#else
	return Convert_SJIS_To_UTF8(src, pOut);
#endif
}

bool Convert_TCHAR_To_UTF16(const TString& src, std::wstring* pOut)
{
#ifdef _UNICODE
	*pOut = src;
	return true;
#else
	return Convert_SJIS_To_UTF16(src, pOut);
#endif
}





//===================================================================
// Convert_TCHAR_To_SJIS
//===================================================================

TString ToTString(const std::string& str)
{
#ifdef _UNICODE
	return ToUTF16(str);
#else
	return str;
#endif
}

//-----------------------------------------------------------------------------------

TString ToTString(const std::wstring& str)
{
#ifdef _UNICODE
	return str;
#else
	return ToSJIS(str);
#endif
}

//-----------------------------------------------------------------------------------

std::string ToString(const std::string& str)
{
	return str;
}

std::string ToString(const std::wstring& str)
{
#ifdef KN_CHAR_UTF8
	return ToUTF8(str);
#else
	return ToSJIS(str);
#endif
}

//-----------------------------------------------------------------------------------

std::wstring ToUTF16(const std::string& str)
{
	std::wstring ret;
	Convert_SJIS_To_UTF16(str, &ret);
	return ret;
}
stringU8 ToUTF8(const std::string& str)
{
	std::string ret;
	Convert_SJIS_To_UTF8(str, &ret);
	return ret;
}
stringU8 ToUTF8(const std::wstring& str)
{
	std::string ret;
	Convert_UTF16_To_UTF8(str, &ret);
	return ret;
}
std::string ToSJIS(const stringU8& str)
{
	std::string ret;
	Convert_UTF8_To_SJIS(str, &ret);
	return ret;
}
std::string ToSJIS(const std::wstring& str)
{
	std::string ret;
	Convert_UTF16_To_SJIS(str, &ret);
	return ret;
}


//先頭の全空白を削除する
void TrimLeft(TString &s)
{
	// find first non-space character
	int i = 0;
	int len = (int)s.length();
	while (i <  len)
	{
		TChar ch = s[i];
		int white =
#ifdef UNICODE
			iswspace(ch);
#else
			isspace(ch);
#endif
		if (!white)
			break;
		++i;
	}

	if (i<len)
		s = s.substr(i);
}



void RemoveFirstLine(TString &src, TString &result)
{
	int breakPosition = (int)src.find(_T('\n'));
	result = _T("");
	if (breakPosition != TString::npos)	//if found...
	{
		int len = (int)src.length();
		result = src.substr(0, breakPosition);
		src = src.substr(breakPosition + 1, (len - breakPosition) - 1);		// skip the '/n'
	}
	else
	{
		result = src;
		src = _T("");
	}
}

int CountLines(const TString &s)
{
	int lines = 0;
	int breakPos = 0;

	do
	{
		++lines;
		breakPos = (int)s.find(_T('\n'), breakPos + 1);
	} while (breakPos != TString::npos);

	return lines;
}


TString ToStr(int num, int base)
{
	gt2_tstringstream ss;
	ss << std::setbase(base);
	ss << num;
	return ss.str();
}  // end ToStr()

TString ToStr(unsigned int num, int base)
{
	gt2_tstringstream ss;
	ss << std::setbase(base);
	ss << num;
	return ss.str();
}

TString ToStr(unsigned long num, int base)
{
	gt2_tstringstream ss;
	ss << std::setbase(base);
	ss << num;
	return ss.str();
}

TString ToStr(float num, int setprecision)
{
	gt2_tstringstream ss;
	ss << std::setprecision(setprecision);
	ss << num;
	return ss.str();
}

TString ToStr(double num, int setprecision)
{
	gt2_tstringstream ss;
	ss << std::setprecision(setprecision);
	ss << num;
	return ss.str();
}

TString ToStr(bool val)
{
	return (TString((val == true ? _T("true") : _T("false"))));
}

//TString ToStr(const gt2Vector3& vec)
//{
//    return TString("(" + ToStr(vec.x) + "," + ToStr(vec.y) + "," + ToStr(vec.z) + ")");
//}



//---------------------------------------------------------------------------------------------------------------------
// これはPerl split()関数のように基本的にある。それは、それぞれの区切り文字でそれを切断することによって
// 文字列にstrを分割します。結果はVECに格納されている。
//---------------------------------------------------------------------------------------------------------------------
void Split(const TString& str, StringVec& vec, char delimiter)
{
	vec.clear();
	size_t strLen = str.size();
	if (strLen == 0)
		return;

	size_t startIndex = 0;
	size_t indexOfDel = str.find_first_of(delimiter, startIndex);
	while (indexOfDel != TString::npos)
	{
		vec.push_back(str.substr(startIndex, indexOfDel - startIndex));
		startIndex = indexOfDel + 1;
		if (startIndex >= strLen)
			break;
		indexOfDel = str.find_first_of(delimiter, startIndex);
	}
	if (startIndex < strLen)
		vec.push_back(str.substr(startIndex));
}

TString ToLower(const TString &in)
{
	const TChar *p = in.c_str();
	TString ret;
	uint32_t n;

	for (n = 0; n < in.length(); ++n)
		if (p[n] <= _T('A') && p[n] >= _T('Z'))
			ret += TChar(p[n] + 32);
		else
			ret += p[n];
	return ret;
}

TString ToUpper(const TString &in)
{
	const TChar *p = in.c_str();
	TString ret;
	uint32_t n;

	for (n = 0; n < in.length(); ++n)
		if (p[n] <= _T('a') && p[n] >= _T('z'))
			ret += TChar(p[n] - 32);
		else
			ret += p[n];
	return ret;
}

