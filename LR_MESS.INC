/*
_________________________________________________________________________
Error/status messages for LR
Serge Kovalyov, March 1993.
_________________________________________________________________________
*/

#ifndef LR_MESS_INC
#define LR_MESS_INC

// Error messages

#define lr_error_text(NAME)             lr_error_##NAME##_text

// The following macro is used to print message (with line number)

#define lr_error_text_and_number(NAME)  lr_error_text(NAME), (*E)->line_number

// Status messages

#define lr_status_text(NAME)            lr_status_##NAME##_text

#define lr_status_set(NAME)             (lr_status = (char *)lr_status_text(NAME))

#ifdef LR_MESSAGE_DEFINE      /* Module with messages definitions */

// Error messages

#define lr_error_define(NAME, text)     const char *lr_error_text(NAME)  = text

// Severe errors

lr_error_define(required,       "Line %-4d: 0001 %d closing parentheses required in grammar source\n");
lr_error_define(ignored,        "Line %-4d: 0002 closing parenthesis ignored\n");
lr_error_define(quote,          "Line %-4d: 0003 closing quote assumed\n");
lr_error_define(name,           "Global   : 0004 NAME missing\n");
lr_error_define(rules,          "Global   : 0005 RULES missing\n");
lr_error_define(start_symbol,   "Global   : 0006 No start symbol\n");
lr_error_define(start_substr,   "Line %-4d: 0007 Start rule is a substring '%s'\n");
lr_error_define(save,           "Global   : 0008 Unable to save");
lr_error_define(terminal,       "Line %-4d: 0009 Invalid terminal option '%s' for terminal '%s'\n");
lr_error_define(non_terminal,   "Line %-4d: 0010 Invalid non terminal option '%s' for non terminal '%s'\n");
lr_error_define(sec_nt,         "Line %-4d: 0011 Secondary rule '%s(%d)' contains a non terminal\n");
lr_error_define(rc_sec_nt,      "Line %-4d: 0012 Rule '%s(%d)' specifies '%s' as a secondary non terminal, but '%s' contains a non terminal\n");
lr_error_define(lhs,            "Line %-4d: 0013 Undefined non terminal '%s'\n");
lr_error_define(nt_option,      "Line %-4d: 0010 Invalid non terminal option '%s'\n");
lr_error_define(str_str,        "Line %-4d: 0014 String '%s' over string '%s' in rule '%s(%d)'\n");
lr_error_define(substr_str,     "Line %-4d: 0015 Substring '%s' over string '%s' in rule '%s(%d)'\n");
lr_error_define(normal_substr,  "Line %-4d: 0016 Normal '%s' over substring '%s' in rule '%s(%d)'\n");
lr_error_define(reduce,         "Line %-4d: 0017 Reduce '%s(%d)' reduce '%s(%d)' at state %d\n");
lr_error_define(mixed,          "Line %-4d: 0018 Mixed rule '%s(%d)'\n");
lr_error_define(zero_production,"Line %-4d: 0019 Zero production in rule '%s(%d)'\n");
lr_error_define(reuse,          "Line %-4d: 0020 Re-use of non terminal '%s' in rule '%s(%d)'\n");
lr_error_define(non_deter,      "0021 Non-determinism");
lr_error_define(ignore_conflict,"Line %-4d: 0022 'Ignore' in definition of non terminal '%s' in rule '%s(%d)' conflicts with 'No Ignore' in rule '%s(%d)'\n");
lr_error_define(second_conflict,"Line %-4d: 0023 'Secondary' in definition of non terminal '%s' in rule '%s(%d)' conflicts with 'Not Secondary' in rule '%s(%d)'\n");
lr_error_define(final,          "Line %-4d: 0024 Unable to locate next state from state %d on '%s(%d)' in rule '%s(%d)'\n");
lr_error_define(doubled,        "Line %-4d: 0025 Double exit from state %d on non terminal '%s'\n");
lr_error_define(overlap,        "Line %-4d: 0026 Terminal symbol overlap on '%s(%d)' in rule '%s(%d)' which affects state %d\n");
lr_error_define(no_shift_reduce,"Line %-4d: 0027 State %d contains neither shift nor reduce (rule component '%s(%d)')\n");

// Informational messages

lr_error_define(title,          "Global   : 0101 TITLE missing\n");
lr_error_define(rhs,            "Line %-4d: 0102 Unused non terminal '%s'\n");
lr_error_define(optional,       "Line %-4d: 0103 Undefined optional '%s'\n");
lr_error_define(secondary,      "Line %-4d: 0104 Undefined secondary '%s'\n");
lr_error_define(string,         "Line %-4d: 0105 Undefined string '%s'\n");
lr_error_define(zero,           "Line %-4d: 0106 Undefined zero '%s'\n");
lr_error_define(repeat,         "Line %-4d: 0107 Undefined repeat '%s'\n");
lr_error_define(choice,         "Line %-4d: 0108 Undefined choice '%s'\n");
lr_error_define(ignore,         "Line %-4d: 0109 Undefined ignore '%s'\n");
lr_error_define(dup_rule_name,  "Line %-4d: 0110 Duplicate rule name '%s' within non terminal '%s'\n");
lr_error_define(reduce_shift,   "Line %-4d: 0111 Reduce-shift conflict from state %d, shift text '%s' or reduce by '%s(%d)'\n");

// Status messages

#define lr_status_define(NAME, text)    const char *lr_status_text(NAME) = text

#define lr_status_default       "0200 No grammar is being compiled"

lr_status_define(inactive,      lr_status_default);
lr_status_define(start,         "0201 Started");
lr_status_define(void_parse,    "0202 Performing void language parse");
lr_status_define(create_nts,    "0203 Creating non terminals");
lr_status_define(create_rcs,    "0204 Creating rule components");
lr_status_define(process_strs,  "0205 Processing string reductions");
lr_status_define(expand_states, "0206 Expanding states");
lr_status_define(reduce_states, "0207 Reducing states");
lr_status_define(remove_states, "0208 Removing unreachable states and actions");
lr_status_define(save,          "0209 Saving LR parse table");
lr_status_define(print,         "0210 Printing LR parse table");
lr_status_define(finish,        "0211 Finished");
lr_status_define(abort,         "0212 Aborted by user");

char *lr_status = lr_status_default;

#else
#define lr_error_extern(NAME)   extern const char *lr_error_text(NAME)
#define lr_status_extern(NAME)  extern const char *lr_status_text(NAME)

extern       char *lr_status;

#endif

#endif