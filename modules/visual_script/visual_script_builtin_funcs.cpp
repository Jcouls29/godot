#include "visual_script_builtin_funcs.h"
#include "math_funcs.h"
#include "object_type_db.h"
#include "reference.h"
#include "func_ref.h"
#include "os/os.h"
#include "variant_parser.h"
#include "io/marshalls.h"

const char* VisualScriptBuiltinFunc::func_name[VisualScriptBuiltinFunc::FUNC_MAX]={
	"sin",
	"cos",
	"tan",
	"sinh",
	"cosh",
	"tanh",
	"asin",
	"acos",
	"atan",
	"atan2",
	"sqrt",
	"fmod",
	"fposmod",
	"floor",
	"ceil",
	"round",
	"abs",
	"sign",
	"pow",
	"log",
	"exp",
	"is_nan",
	"is_inf",
	"ease",
	"decimals",
	"stepify",
	"lerp",
	"dectime",
	"randomize",
	"randi",
	"randf",
	"rand_range",
	"seed",
	"rand_seed",
	"deg2rad",
	"rad2deg",
	"linear2db",
	"db2linear",
	"max",
	"min",
	"clamp",
	"nearest_po2",
	"weakref",
	"funcref",
	"convert",
	"typeof",
	"type_exists",
	"str",
	"print",
	"printerr",
	"printraw",
	"var2str",
	"str2var",
	"var2bytes",
	"bytes2var",
};



int VisualScriptBuiltinFunc::get_output_sequence_port_count() const {

	return 1;
}

bool VisualScriptBuiltinFunc::has_input_sequence_port() const{

	return true;
}

int VisualScriptBuiltinFunc::get_input_value_port_count() const{


	switch(func) {

		case MATH_RANDOMIZE:
		case MATH_RAND:
		case MATH_RANDF:
			return 0;
		case MATH_SIN:
		case MATH_COS:
		case MATH_TAN:
		case MATH_SINH:
		case MATH_COSH:
		case MATH_TANH:
		case MATH_ASIN:
		case MATH_ACOS:
		case MATH_ATAN:
		case MATH_SQRT:
		case MATH_FLOOR:
		case MATH_CEIL:
		case MATH_ROUND:
		case MATH_ABS:
		case MATH_SIGN:
		case MATH_LOG:
		case MATH_EXP:
		case MATH_ISNAN:
		case MATH_ISINF:
		case MATH_DECIMALS:
		case MATH_SEED:
		case MATH_RANDSEED:
		case MATH_DEG2RAD:
		case MATH_RAD2DEG:
		case MATH_LINEAR2DB:
		case MATH_DB2LINEAR:
		case LOGIC_NEAREST_PO2:
		case OBJ_WEAKREF:
		case TYPE_OF:
		case TEXT_STR:
		case TEXT_PRINT:
		case TEXT_PRINTERR:
		case TEXT_PRINTRAW:
		case VAR_TO_STR:
		case STR_TO_VAR:
		case VAR_TO_BYTES:
		case BYTES_TO_VAR:
		case TYPE_EXISTS:
			return 1;
		case MATH_ATAN2:
		case MATH_FMOD:
		case MATH_FPOSMOD:
		case MATH_POW:
		case MATH_EASE:
		case MATH_STEPIFY:
		case MATH_RANDOM:
		case LOGIC_MAX:
		case LOGIC_MIN:
		case FUNC_FUNCREF:
		case TYPE_CONVERT:
			return 2;
		case MATH_LERP:
		case MATH_DECTIME:
		case LOGIC_CLAMP:
			return 3;
		case FUNC_MAX:{}

	}
	return 0;
}
int VisualScriptBuiltinFunc::get_output_value_port_count() const{

	switch(func) {
		case MATH_RANDOMIZE:
		case TEXT_PRINT:
		case TEXT_PRINTERR:
		case TEXT_PRINTRAW:
		case MATH_SEED:
			return 0;
		case MATH_RANDSEED:
			return 2;
		default:
			return 1;
	}

	return 1;
}

String VisualScriptBuiltinFunc::get_output_sequence_port_text(int p_port) const {

	return String();
}

PropertyInfo VisualScriptBuiltinFunc::get_input_value_port_info(int p_idx) const{

	switch(func) {

		case MATH_SIN:
		case MATH_COS:
		case MATH_TAN:
		case MATH_SINH:
		case MATH_COSH:
		case MATH_TANH:
		case MATH_ASIN:
		case MATH_ACOS:
		case MATH_ATAN:
		case MATH_ATAN2:
		case MATH_SQRT: {
			return PropertyInfo(Variant::REAL,"num");
		} break;
		case MATH_FMOD:
		case MATH_FPOSMOD: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"x");
			else
				return PropertyInfo(Variant::REAL,"y");
		} break;
		case MATH_FLOOR:
		case MATH_CEIL:
		case MATH_ROUND:
		case MATH_ABS:
		case MATH_SIGN: {
			return PropertyInfo(Variant::REAL,"num");

		} break;

		case MATH_POW: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"x");
			else
				return PropertyInfo(Variant::REAL,"y");
		} break;
		case MATH_LOG:
		case MATH_EXP:
		case MATH_ISNAN:
		case MATH_ISINF: {
			return PropertyInfo(Variant::REAL,"num");
		} break;
		case MATH_EASE: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"s");
			else
				return PropertyInfo(Variant::REAL,"curve");
		} break;
		case MATH_DECIMALS: {
			return PropertyInfo(Variant::REAL,"step");
		} break;
		case MATH_STEPIFY: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"s");
			else
				return PropertyInfo(Variant::REAL,"steps");
		} break;
		case MATH_LERP: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"from");
			else if (p_idx==1)
				return PropertyInfo(Variant::REAL,"to");
			else
				return PropertyInfo(Variant::REAL,"weight");

		} break;
		case MATH_DECTIME: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"value");
			else if (p_idx==1)
				return PropertyInfo(Variant::REAL,"amount");
			else
				return PropertyInfo(Variant::REAL,"step");
		} break;
		case MATH_RANDOMIZE: {

		} break;
		case MATH_RAND: {

		} break;
		case MATH_RANDF: {

		} break;
		case MATH_RANDOM: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"from");
			else
				return PropertyInfo(Variant::REAL,"to");
		} break;
		case MATH_SEED: {
			return PropertyInfo(Variant::INT,"seed");
		} break;
		case MATH_RANDSEED: {
			return PropertyInfo(Variant::INT,"seed");
		} break;
		case MATH_DEG2RAD: {
			return PropertyInfo(Variant::REAL,"deg");
		} break;
		case MATH_RAD2DEG: {
			return PropertyInfo(Variant::REAL,"rad");
		} break;
		case MATH_LINEAR2DB: {
			return PropertyInfo(Variant::REAL,"nrg");
		} break;
		case MATH_DB2LINEAR: {
			return PropertyInfo(Variant::REAL,"db");
		} break;
		case LOGIC_MAX: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"a");
			else
				return PropertyInfo(Variant::REAL,"b");
		} break;
		case LOGIC_MIN: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"a");
			else
				return PropertyInfo(Variant::REAL,"b");
		} break;
		case LOGIC_CLAMP: {
			if (p_idx==0)
				return PropertyInfo(Variant::REAL,"a");
			else if (p_idx==0)
				return PropertyInfo(Variant::REAL,"min");
			else
				return PropertyInfo(Variant::REAL,"max");
		} break;
		case LOGIC_NEAREST_PO2: {
			return PropertyInfo(Variant::INT,"num");
		} break;
		case OBJ_WEAKREF: {

			return PropertyInfo(Variant::OBJECT,"source");

		} break;
		case FUNC_FUNCREF: {

			if (p_idx==0)
				return PropertyInfo(Variant::OBJECT,"instance");
			else
				return PropertyInfo(Variant::STRING,"funcname");

		} break;
		case TYPE_CONVERT: {

			if (p_idx==0)
				return PropertyInfo(Variant::NIL,"what");
			else
				return PropertyInfo(Variant::STRING,"type");
		} break;
		case TYPE_OF: {
			return PropertyInfo(Variant::NIL,"what");

		} break;
		case TYPE_EXISTS: {

			return PropertyInfo(Variant::STRING,"type");

		} break;
		case TEXT_STR: {

			return PropertyInfo(Variant::NIL,"value");


		} break;
		case TEXT_PRINT: {

			return PropertyInfo(Variant::NIL,"value");

		} break;
		case TEXT_PRINTERR: {
			return PropertyInfo(Variant::NIL,"value");

		} break;
		case TEXT_PRINTRAW: {

			return PropertyInfo(Variant::NIL,"value");

		} break;
		case VAR_TO_STR: {
			return PropertyInfo(Variant::NIL,"var");

		} break;
		case STR_TO_VAR: {

			return PropertyInfo(Variant::STRING,"string");
		} break;
		case VAR_TO_BYTES: {
			return PropertyInfo(Variant::NIL,"var");

		} break;
		case BYTES_TO_VAR: {

			return PropertyInfo(Variant::RAW_ARRAY,"bytes");
		} break;
		case FUNC_MAX:{}
	}

	return PropertyInfo();
}

PropertyInfo VisualScriptBuiltinFunc::get_output_value_port_info(int p_idx) const{

	Variant::Type t=Variant::NIL;
	switch(func) {

		case MATH_SIN:
		case MATH_COS:
		case MATH_TAN:
		case MATH_SINH:
		case MATH_COSH:
		case MATH_TANH:
		case MATH_ASIN:
		case MATH_ACOS:
		case MATH_ATAN:
		case MATH_ATAN2:
		case MATH_SQRT:
		case MATH_FMOD:
		case MATH_FPOSMOD:
		case MATH_FLOOR:
		case MATH_CEIL: {
			t=Variant::REAL;
		} break;
		case MATH_ROUND: {
			t=Variant::INT;
		} break;
		case MATH_ABS: {
			t=Variant::NIL;
		} break;
		case MATH_SIGN: {
			t=Variant::NIL;
		} break;
		case MATH_POW:
		case MATH_LOG:
		case MATH_EXP: {
			t=Variant::REAL;
		} break;
		case MATH_ISNAN:
		case MATH_ISINF: {
			t=Variant::BOOL;
		} break;
		case MATH_EASE: {
			t=Variant::REAL;
		} break;
		case MATH_DECIMALS: {
			t=Variant::INT;
		} break;
		case MATH_STEPIFY:
		case MATH_LERP:
		case MATH_DECTIME: {
			t=Variant::REAL;

		} break;
		case MATH_RANDOMIZE: {

		} break;
		case MATH_RAND: {

			t=Variant::INT;
		} break;
		case MATH_RANDF:
		case MATH_RANDOM: {
			t=Variant::REAL;
		} break;
		case MATH_SEED: {

		} break;
		case MATH_RANDSEED: {

			if (p_idx==0)
				return PropertyInfo(Variant::INT,"rnd");
			else
				return PropertyInfo(Variant::INT,"seed");
		} break;
		case MATH_DEG2RAD:
		case MATH_RAD2DEG:
		case MATH_LINEAR2DB:
		case MATH_DB2LINEAR: {
			t=Variant::REAL;
		} break;
		case LOGIC_MAX:
		case LOGIC_MIN:
		case LOGIC_CLAMP: {


		} break;

		case LOGIC_NEAREST_PO2: {
			t=Variant::NIL;
		} break;
		case OBJ_WEAKREF: {

			t=Variant::OBJECT;

		} break;
		case FUNC_FUNCREF: {

			t=Variant::OBJECT;

		} break;
		case TYPE_CONVERT: {



		} break;
		case TYPE_OF: {
			t=Variant::INT;

		} break;
		case TYPE_EXISTS: {

			t=Variant::BOOL;

		} break;
		case TEXT_STR: {

			t=Variant::STRING;

		} break;
		case TEXT_PRINT: {


		} break;
		case TEXT_PRINTERR: {

		} break;
		case TEXT_PRINTRAW: {

		} break;
		case VAR_TO_STR: {
			t=Variant::STRING;
		} break;
		case STR_TO_VAR: {

		} break;
		case VAR_TO_BYTES: {
			t=Variant::RAW_ARRAY;

		} break;
		case BYTES_TO_VAR: {


		} break;
		case FUNC_MAX:{}
	}

	return PropertyInfo(t,"");
}

String VisualScriptBuiltinFunc::get_caption() const {

	return "BuiltinFunc";
}

String VisualScriptBuiltinFunc::get_text() const {

	return func_name[func];
}

void VisualScriptBuiltinFunc::set_func(BuiltinFunc p_which) {

	ERR_FAIL_INDEX(p_which,FUNC_MAX);
	func=p_which;
	_change_notify();
	ports_changed_notify();
}

VisualScriptBuiltinFunc::BuiltinFunc VisualScriptBuiltinFunc::get_func() {
	return func;
}


#define VALIDATE_ARG_NUM(m_arg) \
	if (!p_inputs[m_arg]->is_num()) {\
		r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;\
		r_error.argument=m_arg;\
		r_error.expected=Variant::REAL;\
		return 0;\
	}

class VisualScriptNodeInstanceBuiltinFunc : public VisualScriptNodeInstance {
public:

	VisualScriptBuiltinFunc *node;
	VisualScriptInstance *instance;

	VisualScriptBuiltinFunc::BuiltinFunc func;


	//virtual int get_working_memory_size() const { return 0; }
	//virtual bool is_output_port_unsequenced(int p_idx) const { return false; }
	//virtual bool get_output_port_unsequenced(int p_idx,Variant* r_value,Variant* p_working_mem,String &r_error) const { return true; }

	virtual int step(const Variant** p_inputs,Variant** p_outputs,StartMode p_start_mode,Variant* p_working_mem,Variant::CallError& r_error,String& r_error_str) {

		switch(func) {
			case VisualScriptBuiltinFunc::MATH_SIN: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::sin(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_COS: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::cos(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_TAN: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::tan(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_SINH: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::sinh(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_COSH: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::cosh(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_TANH: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::tanh(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ASIN: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::asin(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ACOS: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::acos(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ATAN: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::atan(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ATAN2: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				*p_outputs[0]=Math::atan2(*p_inputs[0],*p_inputs[1]);
			} break;
			case VisualScriptBuiltinFunc::MATH_SQRT: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::sqrt(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_FMOD: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				*p_outputs[0]=Math::fmod(*p_inputs[0],*p_inputs[1]);
			} break;
			case VisualScriptBuiltinFunc::MATH_FPOSMOD: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				*p_outputs[0]=Math::fposmod(*p_inputs[0],*p_inputs[1]);
			} break;
			case VisualScriptBuiltinFunc::MATH_FLOOR: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::floor(*p_inputs[0]);
			  } break;
			case VisualScriptBuiltinFunc::MATH_CEIL: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::ceil(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ROUND: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::round(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ABS: {

				if (p_inputs[0]->get_type()==Variant::INT) {

					int64_t i = *p_inputs[0];
					*p_outputs[0]=ABS(i);
				} else if (p_inputs[0]->get_type()==Variant::REAL) {

					real_t r = *p_inputs[0];
					*p_outputs[0]=Math::abs(r);
				} else {

					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::REAL;

				}
			} break;
			case VisualScriptBuiltinFunc::MATH_SIGN: {

					if (p_inputs[0]->get_type()==Variant::INT) {

						int64_t i = *p_inputs[0];
						*p_outputs[0]= i < 0 ? -1 : ( i > 0 ? +1 : 0);
					} else if (p_inputs[0]->get_type()==Variant::REAL) {

						real_t r = *p_inputs[0];
						*p_outputs[0]= r < 0.0 ? -1.0 : ( r > 0.0 ? +1.0 : 0.0);
					} else {

						r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
						r_error.argument=0;
						r_error.expected=Variant::REAL;

					}
			} break;
			case VisualScriptBuiltinFunc::MATH_POW: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				*p_outputs[0]=Math::pow(*p_inputs[0],*p_inputs[1]);
			} break;
			case VisualScriptBuiltinFunc::MATH_LOG: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::log(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_EXP: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::exp(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ISNAN: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::is_nan(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_ISINF: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::is_inf(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_EASE: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				*p_outputs[0]=Math::ease(*p_inputs[0],*p_inputs[1]);
			} break;
			case VisualScriptBuiltinFunc::MATH_DECIMALS: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::step_decimals(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_STEPIFY: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				*p_outputs[0]=Math::stepify(*p_inputs[0],*p_inputs[1]);
			} break;
			case VisualScriptBuiltinFunc::MATH_LERP: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				VALIDATE_ARG_NUM(2);
				*p_outputs[0]=Math::lerp(*p_inputs[0],*p_inputs[1],*p_inputs[2]);
			} break;
			case VisualScriptBuiltinFunc::MATH_DECTIME: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				VALIDATE_ARG_NUM(2);
				*p_outputs[0]=Math::dectime(*p_inputs[0],*p_inputs[1],*p_inputs[2]);
			} break;
			case VisualScriptBuiltinFunc::MATH_RANDOMIZE: {
				Math::randomize();

			} break;
			case VisualScriptBuiltinFunc::MATH_RAND: {
				*p_outputs[0]=Math::rand();
			} break;
			case VisualScriptBuiltinFunc::MATH_RANDF: {
				*p_outputs[0]=Math::randf();
			} break;
			case VisualScriptBuiltinFunc::MATH_RANDOM: {

				VALIDATE_ARG_NUM(0);
				VALIDATE_ARG_NUM(1);
				*p_outputs[0]=Math::random(*p_inputs[0],*p_inputs[1]);
			} break;
			case VisualScriptBuiltinFunc::MATH_SEED: {

				VALIDATE_ARG_NUM(0);
				uint32_t seed=*p_inputs[0];
				Math::seed(seed);

			} break;
			case VisualScriptBuiltinFunc::MATH_RANDSEED: {

				VALIDATE_ARG_NUM(0);
				uint32_t seed=*p_inputs[0];
				int ret = Math::rand_from_seed(&seed);
				Array reta;
				reta.push_back(ret);
				reta.push_back(seed);
				*p_outputs[0]=reta;

			} break;
			case VisualScriptBuiltinFunc::MATH_DEG2RAD: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::deg2rad(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_RAD2DEG: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::rad2deg(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_LINEAR2DB: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::linear2db(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::MATH_DB2LINEAR: {

				VALIDATE_ARG_NUM(0);
				*p_outputs[0]=Math::db2linear(*p_inputs[0]);
			} break;
			case VisualScriptBuiltinFunc::LOGIC_MAX: {

				if (p_inputs[0]->get_type()==Variant::INT && p_inputs[1]->get_type()==Variant::INT) {

					int64_t a = *p_inputs[0];
					int64_t b = *p_inputs[1];
					*p_outputs[0]=MAX(a,b);
				} else {
					VALIDATE_ARG_NUM(0);
					VALIDATE_ARG_NUM(1);

					real_t a = *p_inputs[0];
					real_t b = *p_inputs[1];

					*p_outputs[0]=MAX(a,b);
				}

			} break;
			case VisualScriptBuiltinFunc::LOGIC_MIN: {

				if (p_inputs[0]->get_type()==Variant::INT && p_inputs[1]->get_type()==Variant::INT) {

					int64_t a = *p_inputs[0];
					int64_t b = *p_inputs[1];
					*p_outputs[0]=MIN(a,b);
				} else {
					VALIDATE_ARG_NUM(0);
					VALIDATE_ARG_NUM(1);

					real_t a = *p_inputs[0];
					real_t b = *p_inputs[1];

					*p_outputs[0]=MIN(a,b);
				}
			} break;
			case VisualScriptBuiltinFunc::LOGIC_CLAMP: {

				if (p_inputs[0]->get_type()==Variant::INT && p_inputs[1]->get_type()==Variant::INT && p_inputs[2]->get_type()==Variant::INT) {

					int64_t a = *p_inputs[0];
					int64_t b = *p_inputs[1];
					int64_t c = *p_inputs[2];
					*p_outputs[0]=CLAMP(a,b,c);
				} else {
					VALIDATE_ARG_NUM(0);
					VALIDATE_ARG_NUM(1);
					VALIDATE_ARG_NUM(2);

					real_t a = *p_inputs[0];
					real_t b = *p_inputs[1];
					real_t c = *p_inputs[2];

					*p_outputs[0]=CLAMP(a,b,c);
				}
			} break;
			case VisualScriptBuiltinFunc::LOGIC_NEAREST_PO2: {

				VALIDATE_ARG_NUM(0);
				int64_t num = *p_inputs[0];
				*p_outputs[0] = nearest_power_of_2(num);
			} break;
			case VisualScriptBuiltinFunc::OBJ_WEAKREF: {

				if (p_inputs[0]->get_type()!=Variant::OBJECT) {

					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::OBJECT;

					return 0;

				}

				if (p_inputs[0]->is_ref()) {

					REF r = *p_inputs[0];
					if (!r.is_valid()) {

						return 0;
					}

					Ref<WeakRef> wref = memnew( WeakRef );
					wref->set_ref(r);
					*p_outputs[0]=wref;
				} else {
					Object *obj = *p_inputs[0];
					if (!obj) {

						return 0;
					}
					Ref<WeakRef> wref = memnew( WeakRef );
					wref->set_obj(obj);
					*p_outputs[0]=wref;
				}




			} break;
			case VisualScriptBuiltinFunc::FUNC_FUNCREF: {

				if (p_inputs[0]->get_type()!=Variant::OBJECT) {

					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::OBJECT;

					return 0;

				}
				if (p_inputs[1]->get_type()!=Variant::STRING && p_inputs[1]->get_type()!=Variant::NODE_PATH) {

					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=1;
					r_error.expected=Variant::STRING;

					return 0;

				}

				Ref<FuncRef> fr = memnew( FuncRef);

				fr->set_instance(*p_inputs[0]);
				fr->set_function(*p_inputs[1]);

				*p_outputs[0]=fr;

			} break;
			case VisualScriptBuiltinFunc::TYPE_CONVERT: {

				VALIDATE_ARG_NUM(1);
				int type=*p_inputs[1];
				if (type<0 || type>=Variant::VARIANT_MAX) {

					*p_outputs[0]=RTR("Invalid type argument to convert(), use TYPE_* constants.");
					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::INT;
					return 0;

				} else {


					*p_outputs[0]=Variant::construct(Variant::Type(type),p_inputs,1,r_error);
				}
			} break;
			case VisualScriptBuiltinFunc::TYPE_OF: {


				*p_outputs[0] = p_inputs[0]->get_type();

			} break;
			case VisualScriptBuiltinFunc::TYPE_EXISTS: {


				*p_outputs[0] = ObjectTypeDB::type_exists(*p_inputs[0]);

			} break;
			case VisualScriptBuiltinFunc::TEXT_STR: {

				String str = *p_inputs[0];

				*p_outputs[0]=str;

			} break;
			case VisualScriptBuiltinFunc::TEXT_PRINT: {

				String str = *p_inputs[0];
				print_line(str);


			} break;

			case VisualScriptBuiltinFunc::TEXT_PRINTERR: {

				String str = *p_inputs[0];

				//str+="\n";
				OS::get_singleton()->printerr("%s\n",str.utf8().get_data());


			} break;
			case VisualScriptBuiltinFunc::TEXT_PRINTRAW: {
				String str = *p_inputs[0];

				//str+="\n";
				OS::get_singleton()->print("%s",str.utf8().get_data());


			} break;
			case VisualScriptBuiltinFunc::VAR_TO_STR: {

				String vars;
				VariantWriter::write_to_string(*p_inputs[0],vars);
				*p_outputs[0]=vars;
			} break;
			case VisualScriptBuiltinFunc::STR_TO_VAR: {

				if (p_inputs[0]->get_type()!=Variant::STRING) {
					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::STRING;

					return 0;
				}

				VariantParser::StreamString ss;
				ss.s=*p_inputs[0];

				String errs;
				int line;
				Error err = VariantParser::parse(&ss,*p_outputs[0],errs,line);

				if (err!=OK) {
					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::STRING;
					*p_outputs[0]="Parse error at line "+itos(line)+": "+errs;
					return 0;
				}

			} break;
			case VisualScriptBuiltinFunc::VAR_TO_BYTES: {


				ByteArray barr;
				int len;
				Error err = encode_variant(*p_inputs[0],NULL,len);
				if (err) {
					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::NIL;
					*p_outputs[0]="Unexpected error encoding variable to bytes, likely unserializable type found (Object or RID).";
					return 0;
				}

				barr.resize(len);
				{
					ByteArray::Write w = barr.write();
					encode_variant(*p_inputs[0],w.ptr(),len);

				}
				*p_outputs[0]=barr;
			} break;
			case VisualScriptBuiltinFunc::BYTES_TO_VAR: {

				if (p_inputs[0]->get_type()!=Variant::RAW_ARRAY) {
					r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
					r_error.argument=0;
					r_error.expected=Variant::RAW_ARRAY;

					return 0;
				}

				ByteArray varr=*p_inputs[0];
				Variant ret;
				{
					ByteArray::Read r=varr.read();
					Error err = decode_variant(ret,r.ptr(),varr.size(),NULL);
					if (err!=OK) {
						*p_outputs[0]=RTR("Not enough bytes for decoding bytes, or invalid format.");
						r_error.error=Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
						r_error.argument=0;
						r_error.expected=Variant::RAW_ARRAY;
						return 0;
					}

				}

				*p_outputs[0]=ret;

			} break;
			default: {}
		}
		return 0;
	}


};

VisualScriptNodeInstance* VisualScriptBuiltinFunc::instance(VisualScriptInstance* p_instance) {

	VisualScriptNodeInstanceBuiltinFunc * instance = memnew(VisualScriptNodeInstanceBuiltinFunc );
	instance->node=this;
	instance->instance=p_instance;
	instance->func=func;
	return instance;
}


void VisualScriptBuiltinFunc::_bind_methods() {

	ObjectTypeDB::bind_method(_MD("set_func","which"),&VisualScriptBuiltinFunc::set_func);
	ObjectTypeDB::bind_method(_MD("get_func"),&VisualScriptBuiltinFunc::get_func);

	String cc;

	for(int i=0;i<FUNC_MAX;i++) {

		if (i>0)
			cc+=",";
		cc+=func_name[i];
	}
	ADD_PROPERTY(PropertyInfo(Variant::INT,"function",PROPERTY_HINT_ENUM,cc),_SCS("set_func"),_SCS("get_func"));
}

VisualScriptBuiltinFunc::VisualScriptBuiltinFunc() {

	func=MATH_SIN;
}

template<VisualScriptBuiltinFunc::BuiltinFunc func>
static Ref<VisualScriptNode> create_builtin_func_node(const String& p_name) {

	Ref<VisualScriptBuiltinFunc> node;
	node.instance();
	node->set_func(func);
	return node;
}

void register_visual_script_builtin_func_node() {


	VisualScriptLanguage::singleton->add_register_func("functions/built_in/sin",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_SIN>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/cos",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_COS>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/tan",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_TAN>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/sinh",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_SINH>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/cosh",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_COSH>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/tanh",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_TANH>);

	VisualScriptLanguage::singleton->add_register_func("functions/built_in/asin",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ASIN>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/acos",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ACOS>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/atan",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ATAN>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/atan2",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ATAN2>);

	VisualScriptLanguage::singleton->add_register_func("functions/built_in/sqrt",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_SQRT>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/fmod",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_FMOD>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/fposmod",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_FPOSMOD>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/floor",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_FLOOR>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/ceil",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_CEIL>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/round",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ROUND>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/abs",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ABS>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/sign",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_SIGN>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/pow",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_POW>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/log",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_LOG>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/exp",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_EXP>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/isnan",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ISNAN>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/isinf",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_ISINF>);

	VisualScriptLanguage::singleton->add_register_func("functions/built_in/ease",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_EASE>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/decimals",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_DECIMALS>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/stepify",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_STEPIFY>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/lerp",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_LERP>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/dectime",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_DECTIME>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/randomize",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_RANDOMIZE>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/rand",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_RAND>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/randf",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_RANDF>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/random",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_RANDOM>);

	VisualScriptLanguage::singleton->add_register_func("functions/built_in/seed",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_SEED>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/randseed",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_RANDSEED>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/deg2rad",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_DEG2RAD>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/rad2deg",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_RAD2DEG>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/linear2db",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_LINEAR2DB>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/db2linear",create_builtin_func_node<VisualScriptBuiltinFunc::MATH_DB2LINEAR>);

	VisualScriptLanguage::singleton->add_register_func("functions/built_in/max",create_builtin_func_node<VisualScriptBuiltinFunc::LOGIC_MAX>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/min",create_builtin_func_node<VisualScriptBuiltinFunc::LOGIC_MIN>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/clamp",create_builtin_func_node<VisualScriptBuiltinFunc::LOGIC_CLAMP>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/nearest_po2",create_builtin_func_node<VisualScriptBuiltinFunc::LOGIC_NEAREST_PO2>);

	VisualScriptLanguage::singleton->add_register_func("functions/built_in/weakref",create_builtin_func_node<VisualScriptBuiltinFunc::OBJ_WEAKREF>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/funcref",create_builtin_func_node<VisualScriptBuiltinFunc::FUNC_FUNCREF>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/convert",create_builtin_func_node<VisualScriptBuiltinFunc::TYPE_CONVERT>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/typeof",create_builtin_func_node<VisualScriptBuiltinFunc::TYPE_OF>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/type_exists",create_builtin_func_node<VisualScriptBuiltinFunc::TYPE_EXISTS>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/str",create_builtin_func_node<VisualScriptBuiltinFunc::TEXT_STR>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/print",create_builtin_func_node<VisualScriptBuiltinFunc::TEXT_PRINT>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/printerr",create_builtin_func_node<VisualScriptBuiltinFunc::TEXT_PRINTERR>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/printraw",create_builtin_func_node<VisualScriptBuiltinFunc::TEXT_PRINTRAW>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/var2str",create_builtin_func_node<VisualScriptBuiltinFunc::VAR_TO_STR>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/str2var",create_builtin_func_node<VisualScriptBuiltinFunc::STR_TO_VAR>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/var2bytes",create_builtin_func_node<VisualScriptBuiltinFunc::VAR_TO_BYTES>);
	VisualScriptLanguage::singleton->add_register_func("functions/built_in/bytes2var",create_builtin_func_node<VisualScriptBuiltinFunc::BYTES_TO_VAR>);

}
