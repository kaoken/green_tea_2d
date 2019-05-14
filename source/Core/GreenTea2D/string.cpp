#include "../greenTea2D.h"
#include <unicode/utypes.h>
#include <unicode/uclean.h>
#include <unicode/ucnv.h>
#include <unicode/umachine.h>
#include <string.h>


/** �쐬���ꂽ�������[�̃`�F�b�N
 * 
 */

#define CNV_MEM_CHECK(_funcName, _pp) \
	if (*_pp == nullptr) { \
		Trace(_funcName, ICU_ErrorString(U_MEMORY_ALLOCATION_ERROR)); \
		ret = false; \
		goto UCNV_END; \
	}


/*!
* @brief ICU�p�̃G���[������擾�֐�
* @param [in]  error  �G���[�̎��
* @return �G���[�������Ԃ�
*/
static const TChar* ICU_ErrorString(const UErrorCode error)
{
	switch (error)
	{
	case U_USING_FALLBACK_WARNING: return _T("���\�[�X�o���h���̌����́A�t�H�[���o�b�N�̌��ʁi�G���[�ł͂Ȃ��j��Ԃ��܂���");
		//		case U_ERROR_WARNING_START: return _T("��񌋉ʁi�Ӗ��I�ɐ��������j�̊J�n");
	case U_USING_DEFAULT_WARNING: return _T("���\�[�X�o���h�������̓��[�g���P�[���i�G���[�ł͂Ȃ��j�̌��ʂ�Ԃ��܂���");
	case U_SAFECLONE_ALLOCATED_WARNING: return _T("SafeClone����̓������i���̂݁j�����蓖�Ă�K�v������܂���");
	case U_STATE_OLD_WARNING: return _T("ICU�́A�T�[�r�X���\�����邽�߂ɁA�݊������C�����g�p���Ȃ���΂Ȃ�Ȃ��B\n�p�t�H�[�}���X/�������g�p�ʂ̒ቺ�����҂��A�A�b�v�O���[�h���������Ă�������");
	case U_STRING_NOT_TERMINATED_WARNING: return _T("�o�͕����񂪂��邽�� \"�o�͂̒���==destCapacity\" nullptr�ŏI�����邱�Ƃ��ł��܂���ł���");
	case U_SORT_KEY_TOO_SHORT_WARNING: return _T("getBound�ŗv�����ꂽ���x���̐��́A�\�[�g�L�[�̃��x�������������Ȃ��Ă��܂�");
	case U_AMBIGUOUS_ALIAS_WARNING: return _T("���̃R���o�[�^�̕ʖ��͈قȂ�R���o�[�^�̎����ɍs�����Ƃ��ł��܂�");
	case U_DIFFERENT_UCA_VERSION: return _T("ucol_open��UCA�o�[�W�����Əƍ��C���[�W�̃o�[�W�����̊Ԃɕs��v�����������̂ŁA�ƍ��́A���[������\�z���ꂽ�B\n�X�Ɋ֐��ւ̉e���͂���܂���B");
	case U_PLUGIN_CHANGED_LEVEL_WARNING: return _T("�v���O�C���́A���x���̕ω��������N�������B\n�G���[�ł͂Ȃ���������Ȃ����A��Ƀv���O�C�����ǂݍ��܂�Ȃ����Ƃ�����܂��B");
	case U_ERROR_WARNING_LIMIT: return _T("����́A���UErrorCode�̌x���i�Ō�̌x���R�[�h+1�j�̐������������߂ɍŌ�̌x���l�łȂ���΂Ȃ�܂���B");
	case U_ZERO_ERROR: return _T("�G���[�Ȃ��A�x���Ȃ��B");
	case U_ILLEGAL_ARGUMENT_ERROR: return _T("���s�������R�[�h�̊J�n");
	case U_MISSING_RESOURCE_ERROR: return _T("�v�����ꂽ���\�[�X��������܂���");
	case U_INVALID_FORMAT_ERROR: return _T("�f�[�^�t�H�[�}�b�g�����҂���Ȃ����́B");
	case U_FILE_ACCESS_ERROR: return _T("�v�����ꂽ�t�@�C����������܂���B");
	case U_INTERNAL_PROGRAM_ERROR: return _T("���C�u�����̃R�[�h�Ƀo�O�����邱�Ƃ������܂��B");
	case U_MESSAGE_PARSE_ERROR: return _T("���b�Z�[�W�i���b�Z�[�W�E�t�H�[�}�b�g�j����͂��邱�Ƃ��ł��܂���B");
	case U_MEMORY_ALLOCATION_ERROR: return _T("���������蓖�ăG���[");
	case U_INDEX_OUTOFBOUNDS_ERROR: return _T("�͈͊O�̃C���f�b�N�X�ɃA�N�Z�X���悤�Ƃ��Ă��܂�");
	case U_PARSE_ERROR: return _T("Java��ParseException���ɑ���");
	case U_INVALID_CHAR_FOUND: return _T("�����ϊ��F�}�b�s���O�s�\���̓V�[�P���X�B\n����API�̏ꍇ�F�����ȕ����B");
	case U_TRUNCATED_CHAR_FOUND: return _T("�����ϊ��F�s���S�ȓ��̓V�[�P���X�B");
	case U_ILLEGAL_CHAR_FOUND: return _T("�����ϊ��F�s�����̓V�[�P���X/���̓��j�b�g�̑g�ݍ��킹�B");
	case U_INVALID_TABLE_FORMAT: return _T("�ϊ��e�[�u���t�@�C����������܂������A�j�������B");
	case U_INVALID_TABLE_FILE: return _T("�ϊ��e�[�u���t�@�C����������܂���B");
	case U_BUFFER_OVERFLOW_ERROR: return _T("���ʂ́A�w�肳�ꂽ�o�b�t�@�Ɏ��܂�Ȃ����낤�B");
	case U_UNSUPPORTED_ERROR: return _T("�v�����ꂽ����́A���݂̃R���e�L�X�g�ł̓T�|�[�g����܂���B");
	case U_RESOURCE_TYPE_MISMATCH: return _T("����́A������T�|�[�g���Ă��Ȃ����\�[�X����ėv�������B");
	case U_ILLEGAL_ESCAPE_SEQUENCE: return _T("�s����ISO-2022�G�X�P�[�v�V�[�P���X�B");
	case U_UNSUPPORTED_ESCAPE_SEQUENCE: return _T("�T�|�[�g����Ă��Ȃ�ISO-2022�G�X�P�[�v�V�[�P���X�B");
	case U_NO_SPACE_AVAILABLE: return _T("���`�A���r�A��̂��߂Ƀo�b�t�@�g���̂��߂̗��p�\�ȃX�y�[�X������܂���B");
	case U_CE_NOT_FOUND_ERROR: return _T("���ݎg�p����Ă����p�ϐ��g�b�v��ݒ肷�邪�A��ʓI�Ɏg�p�ł����B");
	case U_PRIMARY_TOO_LONG_ERROR: return _T("���[�U�[��2�o�C�g��蒷����ȕϐ��g�b�v��ݒ肵�悤�Ƃ��܂����B");
	case U_STATE_TOO_OLD_ERROR: return _T("ICU�́A���̏�Ԃ���T�[�r�X���\�z���邱�Ƃ��ł��Ȃ����̂Ƃ��āA����͂��͂�T�|�[�g����Ă��܂���B");
	case U_TOO_MANY_ALIASES_ERROR: return _T("���܂�ɂ������̃G�C���A�X���v�����ꂽ���\�[�X�ւ̃p�X������B\n����́A�~�`�̕ʖ���`�����������\�������ɂ���܂��B");
	case U_ENUM_OUT_OF_SYNC_ERROR: return _T("��ɂȂ�R���N�V�����Ɠ�����UEnumeration�A�E�g�B");
	case U_INVARIANT_CONVERSION_ERROR: return _T("�s�σR���o�[�^��char *��UCHAR*�������ϊ��ł��܂���B");
	case U_INVALID_STATE_ERROR: return _T("�v�����ꂽ����́A���݂̏�Ԃ�ICU�Ŋ������邱�Ƃ��ł��܂���B");
	case U_COLLATOR_VERSION_MISMATCH: return _T("�ƍ��o�[�W�����́A�x�[�X�o�[�W�����ƌ݊���������܂���B");
	case U_USELESS_COLLATOR_ERROR: return _T("�ƍ��̓I�v�V���������ŁA�S���x�[�X���w�肳��Ă��܂���B");
	case U_NO_WRITE_PERMISSION: return _T("�ǂݎ���p�܂��͒萔�f�[�^��ύX���悤�B");
	case U_STANDARD_ERROR_LIMIT: return _T("����͏�ɕW���덷�̌��E���������߂ɍŌ�̒l�łȂ���΂Ȃ�܂���B");
	case U_BAD_VARIABLE_DEFINITION: return _T("'$'���݂���Ȃ��܂��͕ϐ������d���B");
		//		case U_PARSE_ERROR_START: return _T("Transliterator�G���[�̊J�n�B");
	case U_MALFORMED_RULE: return _T("���[���̗v�f���݂���Ȃ��B");
	case U_MALFORMED_SET: return _T("UnicodeSet�p�^�[���������ł��B");
	case U_MALFORMED_SYMBOL_REFERENCE: return _T("CU2.4�Ƃ���UNUSED�B");
	case U_MALFORMED_UNICODE_ESCAPE: return _T("Unicode�G�X�P�[�v�p�^�[���������ł��B");
	case U_MALFORMED_VARIABLE_DEFINITION: return _T("�ϐ���`�������ł��B");
	case U_MALFORMED_VARIABLE_REFERENCE: return _T("�ϐ��Q�Ƃ������ł��B");
	case U_MISMATCHED_SEGMENT_DELIMITERS: return _T("CU2.4�Ƃ���UNUSED�B");
	case U_MISPLACED_ANCHOR_START: return _T("�J�n�A���J�[�͕s���ʒu�ŕ\������܂��B");
	case U_MISPLACED_CURSOR_OFFSET: return _T("�I�t�Z�b�g�̓J�[�\�����s���ʒu�Ŕ�������B");
	case U_MISPLACED_QUANTIFIER: return _T("�C���q�́A�Z�O�����g�ɋ߂���؂�L���̌�ɕ\������܂��B");
	case U_MISSING_OPERATOR: return _T("���[�����Ȃ����Z�q���܂܂�Ă��܂���B");
	case U_MISSING_SEGMENT_CLOSE: return _T("CU2.4�Ƃ���UNUSED�B");
	case U_MULTIPLE_ANTE_CONTEXTS: return _T("�������O�R���e�L�X�g�B");
	case U_MULTIPLE_CURSORS: return _T("1�̃J�[�\�����B");
	case U_MULTIPLE_POST_CONTEXTS: return _T("�����̃|�X�g�R���e�L�X�g�B");
	case U_TRAILING_BACKSLASH: return _T("�_���O�����O�o�b�N�X���b�V���B");
	case U_UNDEFINED_SEGMENT_REFERENCE: return _T("�Z�O�����g�̎Q�Ƃ́A��`���ꂽ�Z�O�����g�ɑΉ����Ă��܂���B");
	case U_UNDEFINED_VARIABLE: return _T("�ϐ��̎Q�Ƃ́A��`���ꂽ�ϐ��ɑΉ����Ă��܂���B");
	case U_UNQUOTED_SPECIAL: return _T("���ꕶ���́A�N�H�[�g�܂��̓G�X�P�[�v������Ă��܂���ł����B");
	case U_UNTERMINATED_QUOTE: return _T("����V���O���N�H�[�g���������Ă��܂��B");
	case U_RULE_MASK_ERROR: return _T("���[���͈ȑO����ʓI�ȋK���ɂ���ĉB����Ă��܂��B");
	case U_MISPLACED_COMPOUND_FILTER: return _T("�����t�B���^�������Ȉʒu�ɂ���܂��B");
	case U_MULTIPLE_COMPOUND_FILTERS: return _T("�����̕����t�B���^�[�B");
	case U_INVALID_RBT_SYNTAX: return _T("\"::id\"���[����RuleBasedTransliterator�p�[�T�[�ɓn����܂����B");
	case U_INVALID_PROPERTY_PATTERN: return _T("CU2.4�Ƃ���UNUSED�B");
	case U_MALFORMED_PRAGMA: return _T("'use'�v���O�}�͖����ł��B");
	case U_UNCLOSED_SEGMENT: return _T("����')'���݂���Ȃ��B");
	case U_ILLEGAL_CHAR_IN_SEGMENT: return _T("CU2.4�Ƃ���UNUSED�B");
	case U_VARIABLE_RANGE_EXHAUSTED: return _T("���܂�ɂ������A�X�^���h�C����^����ꂽ�ϐ��͈̔͂̂��߂ɐ����B");
	case U_VARIABLE_RANGE_OVERLAP: return _T("���[���Ŏg�p�����ϐ��͈̔͂Əd�Ȃ镶���B");
	case U_ILLEGAL_CHARACTER: return _T("���ꕶ���͋����ꂽ�R���e�L�X�g�̊O�ɂ���B");
	case U_INTERNAL_TRANSLITERATOR_ERROR: return _T("����transliterator�V�X�e���G���[�B");
	case U_INVALID_ID: return _T("\"::id\"�́A���[�����s����transliterator���w�肵�܂��B");
	case U_INVALID_FUNCTION: return _T("\"&fn()\"�́A���[�����s����transliterator���w�肵�܂��B");
	case U_PARSE_ERROR_LIMIT: return _T("Transliterator�G���[�̌��E�B");
	case U_UNEXPECTED_TOKEN: return _T("�t�H�[�}�b�g�p�^�[���ɍ\���G���[������܂��B");
		//		case U_FMT_PARSE_ERROR_START: return _T("�t�H�[�}�b�g�E���C�u�����G���[�̊J�n�B");
	case U_MULTIPLE_DECIMAL_SEPARATORS: return _T("�ԍ��̃p�^�[���ɕ����̏����_�L���B");
		//		case U_MULTIPLE_DECIMAL_SEPERATORS: return _T("�뎚�F����݊����̂��߂ɕێ��B\nU_MULTIPLE_DECIMAL_SEPARATORS���g�p�B");
	case U_MULTIPLE_EXPONENTIAL_SYMBOLS: return _T("�ԍ��̃p�^�[���ɕ����̎w���L���B");
	case U_MALFORMED_EXPONENTIAL_PATTERN: return _T("�w���p�^�[���ŃV���{�����O���[�v������B");
	case U_MULTIPLE_PERCENT_SYMBOLS: return _T("�ԍ��̃p�^�[���ŕ����̃p�[�Z���g�L���B");
	case U_MULTIPLE_PERMILL_SYMBOLS: return _T("�ԍ��̃p�^�[���ŕ����̃p�[�~���L���B");
	case U_MULTIPLE_PAD_SPECIFIERS: return _T("�ԍ��̃p�^�[���ŕ����̃p�b�h�V���{���B");
	case U_PATTERN_SYNTAX_ERROR: return _T("�t�H�[�}�b�g�p�^�[���ɍ\���G���[������܂��B");
	case U_ILLEGAL_PAD_POSITION: return _T("�p�b�h�L���͔ԍ��p�^�[���ŕ������B");
	case U_UNMATCHED_BRACES: return _T("�����ʂ́A���b�Z�[�W�p�^�[���Ɉ�v���Ă��܂���B");
	case U_UNSUPPORTED_PROPERTY: return _T("ICU2.4�Ƃ���UNUSED�B");
	case U_UNSUPPORTED_ATTRIBUTE: return _T("ICU2.4�Ƃ���UNUSED�B");
	case U_ARGUMENT_TYPE_MISMATCH: return _T("MessageFormat�̊֐��̈������ƈ����C���f�b�N�X�̕s��v�B");
	case U_DUPLICATE_KEYWORD: return _T("�����`�̃L�[���[�h�𕡐����܂��B");
	case U_UNDEFINED_KEYWORD: return _T("����`�E�����̃L�[���[�h�B");
	case U_DEFAULT_KEYWORD_MISSING: return _T("�����̃��[���Ńf�t�H���g���[��������܂���B");
	case U_DECIMAL_NUMBER_SYNTAX_ERROR: return _T("10���̍\���G���[�B");
	case U_FORMAT_INEXACT_ERROR: return _T("���m�ɐ��l���t�H�[�}�b�g���Ċۂߌ덷���[�h�́AROUND_UNNECESSARY�ł��邱�Ƃ͂ł��܂���B����FICU4.8");
	case U_FMT_PARSE_ERROR_LIMIT: return _T("�t�H�[�}�b�g�E���C�u�����̃G���[�̌��E�B");
	case U_BRK_INTERNAL_ERROR: return _T("�����G���[�i�o�O�j�����o����܂����B");
		//		case U_BRK_ERROR_START: return _T("�u���[�N�C�e���[�^�̎��s�������R�[�h�̊J�n�B");
	case U_BRK_HEX_DIGITS_EXPECTED: return _T("16�i���́A���[���ŃG�X�P�[�v����char�^�̈ꕔ�Ƃ��Ċ��ҁB");
	case U_BRK_SEMICOLON_EXPECTED: return _T("RBBI���[���̏I����';'���݂���Ȃ��B");
	case U_BRK_RULE_SYNTAX: return _T("RBBI���[���ɍ\���G���[������܂��B");
	case U_BRK_UNCLOSED_SET: return _T("�N���[�W���O']'���s�����Ă���RBBI���[����������UnicodeSet�B");
	case U_BRK_ASSIGN_ERROR: return _T("RBBI���[��������ɍ\���G���[������܂��B");
	case U_BRK_VARIABLE_REDFINITION: return _T("RBBI���[��$�ϐ����Ē�`�B");
	case U_BRK_MISMATCHED_PAREN: return _T("Mis-matched parentheses in an RBBI rule");
	case U_BRK_NEW_LINE_IN_QUOTED_STRING: return _T("RBBI���[���ŕ�����p��������܂���B");
	case U_BRK_UNDEFINED_VARIABLE: return _T("RBBI���[���Œ�`����Ă��Ȃ�$�ϐ����g�p�B");
	case U_BRK_INIT_ERROR: return _T("�������Ɏ��s�B�l������ICU�f�[�^�̕s�����Ă���B");
	case U_BRK_RULE_EMPTY_SET: return _T("���[���͋��Unicode�̃Z�b�g���܂܂�Ă��܂��B");
	case U_BRK_UNRECOGNIZED_OPTION: return _T("!!�F������Ȃ�RBBI���[�����̃I�v�V�����B");
	case U_BRK_MALFORMED_RULE_TAG: return _T("���[�����{nnn}�^�O�̌`��������������܂���B");
	case U_BRK_ERROR_LIMIT: return _T("����́A��Ƀu���[�N�C�e���[�^�̎��s�̐������������߂ɍŌ�̒l�łȂ���΂Ȃ�܂���B");
	case U_REGEX_INTERNAL_ERROR: return _T("�����G���[�i�o�O�j�����o����܂����B");
		//		case U_REGEX_ERROR_START: return _T("Regexp�̏�Q�������R�[�h�̊J�n�B");
	case U_REGEX_RULE_SYNTAX: return _T("���K�\���p�^�[���̍\���G���[�B");
	case U_REGEX_INVALID_STATE: return _T("�v�����ꂽ����̂��ߖ����ȏ�Ԃ�RegexMatcher�B");
	case U_REGEX_BAD_ESCAPE_SEQUENCE: return _T("�p�^�[���ŔF������Ă��Ȃ��o�b�N�X���b�V���G�X�P�[�v�V�[�P���X�B");
	case U_REGEX_PROPERTY_SYNTAX: return _T("�s����Unicode�̃v���p�e�B�ł��B");
	case U_REGEX_UNIMPLEMENTED: return _T("�܂���������Ă��܂���regexp�֐��̎g�p�B");
	case U_REGEX_MISMATCHED_PAREN: return _T("����Đ��K�\���p�^�[���Ŋ��ʂ��l�X�g���ꂽ�B");
	case U_REGEX_NUMBER_TOO_BIG: return _T("10�i�����傫������B");
	case U_REGEX_BAD_INTERVAL: return _T("{min�Amax}�Ԋu���ɃG���[���������܂����B");
	case U_REGEX_MAX_LT_MIN: return _T("{min�Amax}�ŁAmax��min��菬�����B");
	case U_REGEX_INVALID_BACK_REF: return _T("���݂��Ȃ��L���v�`���O���[�v�ւ̌���Q�ƁB");
	case U_REGEX_INVALID_FLAG: return _T("�}�b�`���[�h�t���O�̒l�������ł��B");
	case U_REGEX_LOOK_BEHIND_LIMIT: return _T("���b�N�r�n�C���h�p�^�[���}�b�`�́A�L�E�ő咷�������Ă���K�v������܂��B");
	case U_REGEX_SET_CONTAINS_STRING: return _T("���K�\���́A��������܂�UnicodeSets�������Ƃ͂ł��܂���B");
	case U_REGEX_OCTAL_TOO_BIG: return _T("8�i�������萔�́A<=0377�ł���K�v������܂��B");
	case U_REGEX_MISSING_CLOSE_BRACKET: return _T("���ʎ��ɕ����ʂ�����܂���B");
	case U_REGEX_INVALID_RANGE: return _T("�����͈͂ɂ�����[x-y]�Ax��y�����傫���B");
	case U_REGEX_STACK_OVERFLOW: return _T("���K�\���o�b�N�g���b�N�X�^�b�N�I�[�o�[�t���[�B");
	case U_REGEX_TIME_OUT: return _T("�ő勖�e��v���Ԃ����߂��܂����B");
	case U_REGEX_STOPPED_BY_CALLER: return _T("�}�b�`���O����́A���[�U�R�[���o�b�NFN�ɂ���Ē��~�B");
	case U_REGEX_ERROR_LIMIT: return _T("����́A��ɐ��K�\���G���[�̌��E���������߂ɍŌ�̒l�łȂ���΂Ȃ�܂���B");
		//		case U_PLUGIN_ERROR_START: return _T("�v���O�C���̏�Q�������R�[�h�̊J�n�B");
	case U_PLUGIN_TOO_HIGH: return _T("�v���O�C���̃��x���͍����[�h����ɂ͍�������B");
	case U_PLUGIN_DIDNT_SET_LEVEL: return _T("�v���O�C���́A�N�G���[�ɉ�����uplug_setPlugLevel���Ăяo���Ȃ������B");
	case U_PLUGIN_ERROR_LIMIT: return _T("����́A��Ƀv���O�C���G���[�̌��E���������߂ɍŌ�̒l�łȂ���΂Ȃ�܂���B");
		//		case U_ERROR_LIMIT 	: return _T("����͏��UErrorCode�i�Ō�̃G���[�R�[�h+1�j�̐������������߂ɍŌ�̒l�łȂ���΂Ȃ�܂���B");
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
//		*ppBffDest = new char[lenDest]; // �o�͗̈�̊m��
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
		*ppUTF8 = new char[lenUTF8]; // �o�͗̈�̊m��
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
	size_t      sourceLength = 0;		// ���͂̒���(�o�C�g��)
	bool ret = true;
	*ppOut = nullptr;

	UConverter* pConv = ucnv_open("sjis", &error); // UConverter�̐���
	if (U_FAILURE(error)) {
		Trace(_T("Convert_SJIS_To_UTF16() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = strlen(pSrc) + 1;

	do
	{
		*ppOut = new UChar[sourceLength]; // �o�͗̈�̊m��
		CNV_MEM_CHECK(_T("Convert_SJIS_To_UTF16() error:%s"), ppOut);
		memset(*ppOut, 0, sourceLength);
		UChar* pPos = *ppOut;
		const char* pIn = pSrc;

		// �}���`�o�C�g������(shift_jis) ���� Unicode �֕ϊ�
		// void ucnv_toUnicode_59(UConverter *,UChar **,const UChar *,const char **,const char *,int32_t *,UBool,UErrorCode *)
		ucnv_toUnicode(
			pConv,					// Unicode�R���o�[�^
			&pPos,					// �o�̓o�b�t�@�̐擪
			pPos + sourceLength,	// �o�̓o�b�t�@�̏��
			&pIn,					// ���̓o�b�t�@�̐擪
			pIn + sourceLength,		// ���̓o�b�t�@�̏��
			0,						// ���0
			TRUE,					// ���̓V�[�P���X�̏I�[�ł����TRUE
			&error					// �G���[�R�[�h
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
	ucnv_close(pConv); // UConverter�̊J��
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
		*ppSjis = new char[lenSJIS]; // �o�͗̈�̊m��
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
	size_t      sourceLength = 0;		// ���͂̒���(�o�C�g��)
	bool ret = true;
	*ppUTF16 = nullptr;

	UConverter* pConv = ucnv_open("utf-8", &error); // UConverter�̐���
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF8_To_UTF16() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = strlen(pUTF8) + 1;


	do
	{
		*ppUTF16 = new UChar[sourceLength]; // �o�͗̈�̊m��
		CNV_MEM_CHECK(_T("Convert_UTF8_To_UTF16() error:%s"), ppUTF16);
		memset(*ppUTF16, 0, sizeof(UChar)*sourceLength);

		UChar* pPos = *ppUTF16;
		const char* pIn = pUTF8;

		// �}���`�o�C�g������(shift_jis) ���� Unicode �֕ϊ�
		ucnv_toUnicode(
			pConv,					// Unicode�R���o�[�^
			&pPos,					// �o�̓o�b�t�@�̐擪
			pPos + sourceLength,	// �o�̓o�b�t�@�̏��
			&pIn,					// ���̓o�b�t�@�̐擪
			pIn + sourceLength,		// ���̓o�b�t�@�̏��
			0,						// ���0
			TRUE,					// ���̓V�[�P���X�̏I�[�ł����TRUE
			&error					// �G���[�R�[�h
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
	ucnv_close(pConv); // UConverter�̊J��
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
	size_t      sourceLength = 0;	// ���͂̒���(�o�C�g��)
	size_t      outLength = 0;		// �o�͂̒���(�o�C�g��)
	bool ret = true;
	*ppOut = nullptr;

	u_init(&error);

	UConverter* pConv = ucnv_open("sjis", &error); // UConverter�̐���
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF16_To_SJIS() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = wcslen((wchar_t*)pSrc);
	outLength = sourceLength * 2 + 1;


	do{
		*ppOut = new char[outLength]; // �o�͗̈�̊m��
		CNV_MEM_CHECK(_T("Convert_UTF16_To_SJIS() error:%s"), ppOut);
		memset(*ppOut, 0, outLength);

		char* pPos = *ppOut;
		const UChar* pIn = pSrc;

		// Unicode ���� �}���`�o�C�g������(shift_jis) �֕ϊ�
		ucnv_fromUnicode(
			pConv,					// Unicode�R���o�[�^
			&pPos,					// �o�̓o�b�t�@�̐擪
			pPos + outLength,		// �o�̓o�b�t�@�̏��
			&pIn,					// ���̓o�b�t�@�̐擪
			pIn + sourceLength,		// ���̓o�b�t�@�̏��
			0,						// ���0
			TRUE,					// ���̓V�[�P���X�̏I�[�ł����TRUE
			&error					// �G���[�R�[�h
			);
		if (U_FAILURE(error)) {
			// �o�b�t�@�T�C�Y���������̂ő傫����蒼��
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
	ucnv_close(pConv); // UConverter�̊J��
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
	size_t      sourceLength = 0;	// ���͂̒���(�o�C�g��)
	size_t      outLength = 0;		// �o�͂̒���(�o�C�g��)
	bool ret = true;
	*ppOut = nullptr;

	u_init(&error);

	UConverter* pConv = ucnv_open("utf-8", &error); // UConverter�̐���
	if (U_FAILURE(error)) {
		Trace(_T("Convert_UTF16_To_UTF8() error:%s"), ICU_ErrorString(error));
		ret = false;
		goto UCNV_END;
	}
	sourceLength = wcslen((wchar_t*)pSrc);
	outLength = sourceLength * 2 + 1;

	do{

		*ppOut = new char[outLength]; // �o�͗̈�̊m��
		CNV_MEM_CHECK(_T("Convert_UTF16_To_UTF8() error:%s"), ppOut);
		memset(*ppOut, 0, outLength);

		char* pPos = *ppOut;
		const UChar* pIn = pSrc;

		// Unicode ���� �}���`�o�C�g������(shift_jis) �֕ϊ�
		ucnv_fromUnicode(
			pConv,					// Unicode�R���o�[�^
			&pPos,					// �o�̓o�b�t�@�̐擪
			pPos + outLength,		// �o�̓o�b�t�@�̏��
			&pIn,					// ���̓o�b�t�@�̐擪
			pIn + sourceLength,		// ���̓o�b�t�@�̏��
			0,						// ���0
			TRUE,					// ���̓V�[�P���X�̏I�[�ł����TRUE
			&error					// �G���[�R�[�h
			);
		if (U_FAILURE(error)) {
			SAFE_DELETE_ARRAY(*ppOut);
			if (error == U_BUFFER_OVERFLOW_ERROR)
			{
				// �o�b�t�@�T�C�Y���������̂ő傫����蒼��
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
	ucnv_close(pConv); // UConverter�̊J��
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


//�擪�̑S�󔒂��폜����
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
// �����Perl split()�֐��̂悤�Ɋ�{�I�ɂ���B����́A���ꂼ��̋�؂蕶���ł����ؒf���邱�Ƃɂ����
// �������str�𕪊����܂��B���ʂ�VEC�Ɋi�[����Ă���B
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

