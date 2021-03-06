/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#define RCSID3 "$Header: mach3.c,v 3.7 90/11/15 15:02:19 ceriel Exp $"

/*
 * INTEL 8086 keywords
 */

0,	R16,		0,		"AX",
0,	R16,		1,		"CX",
0,	R16,		2,		"DX",
0,	R16,		3,		"BX",
0,	R16,		4,		"SP",
0,	R16,		5,		"BP",
0,	R16,		6,		"SI",
0,	R16,		7,		"DI",
0,	R8,		0,		"AL",
0,	R8,		1,		"CL",
0,	R8,		2,		"DL",
0,	R8,		3,		"BL",
0,	R8,		4,		"AH",
0,	R8,		5,		"CH",
0,	R8,		6,		"DH",
0,	R8,		7,		"BH",
0,	RSEG,		0,		"ES",
0,	RSEG,		1,		"CS",
0,	RSEG,		2,		"SS",
0,	RSEG,		3,		"DS",
0,	PREFIX,		046,		"ESEG",
0,	PREFIX,		056,		"CSEG",
0,	PREFIX,		066,		"SSEG",
0,	PREFIX,		076,		"DSEG",
0,	PREFIX,		0360,		"LOCK",
0,	PREFIX,		0362,		"REP",
0,	PREFIX,		0362,		"REPNE",
0,	PREFIX,		0362,		"REPNZ",
0,	PREFIX,		0363,		"REPE",
0,	PREFIX,		0363,		"REPZ",
0,	NOOP_1,		047,		"DAA",
0,	NOOP_1,		057,		"DAS",
0,	NOOP_1,		067,		"AAA",
0,	NOOP_1,		077,		"AAS",
0,	NOOP_1,		0220,		"NOP",
0,	NOOP_1,		0230,		"CBW",
0,	NOOP_1,		0231,		"CWD",
0,	NOOP_1,		0233,		"WAIT",
0,	NOOP_1,		0234,		"PUSHF",
0,	NOOP_1,		0235,		"POPF",
0,	NOOP_1,		0236,		"SAHF",
0,	NOOP_1,		0237,		"LAHF",
0,	NOOP_1,		0244,		"MOVSB",
0,	NOOP_1,		0245,		"MOVS",
0,	NOOP_1,		0245,		"MOVSW",
0,	NOOP_1,		0246,		"CMPSB",
0,	NOOP_1,		0247,		"CMPS",
0,	NOOP_1,		0247,		"CMPSW",
0,	NOOP_1,		0252,		"STOSB",
0,	NOOP_1,		0253,		"STOS",
0,	NOOP_1,		0253,		"STOSW",
0,	NOOP_1,		0254,		"LODSB",
0,	NOOP_1,		0255,		"LODS",
0,	NOOP_1,		0255,		"LODSW",
0,	NOOP_1,		0256,		"SCASB",
0,	NOOP_1,		0257,		"SCAS",
0,	NOOP_1,		0257,		"SCASW",
0,	NOOP_1,		0316,		"INTO",
0,	NOOP_1,		0317,		"IRET",
0,	NOOP_1,		0327,		"XLAT",
0,	NOOP_1,		0364,		"HLT",
0,	NOOP_1,		0365,		"CMC",
0,	NOOP_1,		0370,		"CLC",
0,	NOOP_1,		0371,		"STC",
0,	NOOP_1,		0372,		"CLI",
0,	NOOP_1,		0373,		"STI",
0,	NOOP_1,		0374,		"CLD",
0,	NOOP_1,		0375,		"STD",
0,	NOOP_1,		0017,		"SYS",
0,	NOOP_2,		0324+012<<8,	"AAM",
0,	NOOP_2,		0325+012<<8,	"AAD",
0,	JOP,		0340,		"LOOPNE",
0,	JOP,		0340,		"LOOPNZ",
0,	JOP,		0341,		"LOOPE",
0,	JOP,		0341,		"LOOPZ",
0,	JOP,		0342,		"LOOP",
0,	JOP,		0343,		"JCXZ",
0,	JOP,		0160,		"JO",
0,	JOP,		0161,		"JNO",
0,	JOP,		0162,		"JB",
0,	JOP,		0162,		"JC",
0,	JOP,		0162,		"JNAE",
0,	JOP,		0163,		"JAE",
0,	JOP,		0163,		"JNB",
0,	JOP,		0163,		"JNC",
0,	JOP,		0164,		"JE",
0,	JOP,		0164,		"JZ",
0,	JOP,		0165,		"JNE",
0,	JOP,		0165,		"JNZ",
0,	JOP,		0166,		"JBE",
0,	JOP,		0166,		"JNA",
0,	JOP,		0167,		"JA",
0,	JOP,		0167,		"JNBE",
0,	JOP,		0170,		"JS",
0,	JOP,		0171,		"JNS",
0,	JOP,		0172,		"JP",
0,	JOP,		0172,		"JPE",
0,	JOP,		0173,		"JNP",
0,	JOP,		0173,		"JPO",
0,	JOP,		0174,		"JL",
0,	JOP,		0174,		"JNGE",
0,	JOP,		0175,		"JGE",
0,	JOP,		0175,		"JNL",
0,	JOP,		0176,		"JLE",
0,	JOP,		0176,		"JNG",
0,	JOP,		0177,		"JG",
0,	JOP,		0177,		"JNLE",
0,	PUSHOP,		0,		"PUSH",
0,	PUSHOP,		1,		"POP",
0,	IOOP,		0344,		"INB",
0,	IOOP,		0345,		"IN",
0,	IOOP,		0345,		"INW",
0,	IOOP,		0346,		"OUTB",
0,	IOOP,		0347,		"OUT",
0,	IOOP,		0347,		"OUTW",
0,	ADDOP,		000,		"ADDB",
0,	ADDOP,		001,		"ADD",
0,	ADDOP,		010,		"ORB",
0,	ADDOP,		011,		"OR",
0,	ADDOP,		020,		"ADCB",
0,	ADDOP,		021,		"ADC",
0,	ADDOP,		030,		"SBBB",
0,	ADDOP,		031,		"SBB",
0,	ADDOP,		040,		"ANDB",
0,	ADDOP,		041,		"AND",
0,	ADDOP,		050,		"SUBB",
0,	ADDOP,		051,		"SUB",
0,	ADDOP,		060,		"XORB",
0,	ADDOP,		061,		"XOR",
0,	ADDOP,		070,		"CMPB",
0,	ADDOP,		071,		"CMP",
0,	ROLOP,		000,		"ROLB",
0,	ROLOP,		001,		"ROL",
0,	ROLOP,		010,		"RORB",
0,	ROLOP,		011,		"ROR",
0,	ROLOP,		020,		"RCLB",
0,	ROLOP,		021,		"RCL",
0,	ROLOP,		030,		"RCRB",
0,	ROLOP,		031,		"RCR",
0,	ROLOP,		040,		"SALB",
0,	ROLOP,		040,		"SHLB",
0,	ROLOP,		041,		"SAL",
0,	ROLOP,		041,		"SHL",
0,	ROLOP,		050,		"SHRB",
0,	ROLOP,		051,		"SHR",
0,	ROLOP,		070,		"SARB",
0,	ROLOP,		071,		"SAR",
0,	INCOP,		000,		"INCB",
0,	INCOP,		001,		"INC",
0,	INCOP,		010,		"DECB",
0,	INCOP,		011,		"DEC",
0,	NOTOP,		020,		"NOTB",
0,	NOTOP,		021,		"NOT",
0,	NOTOP,		030,		"NEGB",
0,	NOTOP,		031,		"NEG",
0,	NOTOP,		040,		"MULB",
0,	NOTOP,		041,		"MUL",
0,	NOTOP,		050,		"IMULB",
0,	IMUL,		051,		"IMUL",		/* for 80286 */
0,	NOTOP,		060,		"DIVB",
0,	NOTOP,		061,		"DIV",
0,	NOTOP,		070,		"IDIVB",
0,	NOTOP,		071,		"IDIV",
0,	CALLOP,		020+(0350<<8),	"CALL",
0,	CALLOP,		040+(0351<<8),	"JMP",
0,	CALFOP,		030+(0232<<8),	"CALLF",
0,	CALFOP,		050+(0352<<8),	"JMPF",
0,	LEAOP,		0215,		"LEA",
0,	LEAOP,		0304,		"LES",
0,	LEAOP,		0305,		"LDS",
0,	ESC,		0,		"ESC",
0,	INT,		0,		"INT",
0,	RET,		0303,		"RET",
0,	RET,		0313,		"RETF",
0,	XCHG,		0,		"XCHGB",
0,	XCHG,		1,		"XCHG",
0,	TEST,		0,		"TESTB",
0,	TEST,		1,		"TEST",
0,	MOV,		0,		"MOVB",
0,	MOV,		1,		"MOV",
0,	MOV,		1,		"MOVW",

/* Intel 8087 coprocessor keywords

0,	ST,		0,			"ST",

0,	FNOOP,		FESC+1+(0xF0<<8),	"F2XM1",
0,	FNOOP,		FESC+1+(0xE1<<8),	"FABS",
0,	FNOOP,		FESC+1+(0xE0<<8),	"FCHS",
0,	FNOOP,		FESC+3+(0xE2<<8),	"FCLEX",
0,	FNOOP,		FESC+6+(0xD9<<8),	"FCOMPP",
0,	FNOOP,		FESC+1+(0xF6<<8),	"FDECSTP",
0,	FNOOP,		FESC+3+(0xE1<<8),	"FDISI",
0,	FNOOP,		FESC+3+(0xE0<<8),	"FENI",
0,	FNOOP,		FESC+1+(0xF7<<8),	"FINCSTP",
0,	FNOOP,		FESC+3+(0xE3<<8),	"FINIT",
0,	FNOOP,		FESC+1+(0xE8<<8),	"FLD1",
0,	FNOOP,		FESC+1+(0xEA<<8),	"FLDL2E",
0,	FNOOP,		FESC+1+(0xE9<<8),	"FLDL2T",
0,	FNOOP,		FESC+1+(0xEC<<8),	"FLDLG2",
0,	FNOOP,		FESC+1+(0xED<<8),	"FLDLN2",
0,	FNOOP,		FESC+1+(0xEB<<8),	"FLDPI",
0,	FNOOP,		FESC+1+(0xEE<<8),	"FLDZ",
0,	FNOOP,		FESC+1+(0xD0<<8),	"FNOP",
0,	FNOOP,		FESC+1+(0xF3<<8),	"FPATAN",
0,	FNOOP,		FESC+1+(0xF8<<8),	"FPREM",
0,	FNOOP,		FESC+1+(0xF2<<8),	"FPTAN",
0,	FNOOP,		FESC+1+(0xFC<<8),	"FRNDINT",
0,	FNOOP,		FESC+1+(0xFD<<8),	"FSCALE",
0,	FNOOP,		FESC+1+(0xFA<<8),	"FSQRT",
0,	FNOOP,		FESC+7+(0xE0<<8),	"FSTSWAX", /* 80287 * /
0,	FNOOP,		FESC+1+(0xE4<<8),	"FTST",
0,	FNOOP,		FESC+1+(0xE5<<8),	"FXAM",
0,	FNOOP,		FESC+1+(0xF4<<8),	"FXTRACT",
0,	FNOOP,		FESC+1+(0xF1<<8),	"FYL2X",
0,	FNOOP,		FESC+1+(0xF9<<8),	"FYL2PI",

0,	FMEM,		FESC+6+(0<<11),		"FIADDS",
0,	FMEM,		FESC+2+(0<<11),		"FIADDL",
0,	FMEM,		FESC+0+(0<<11),		"FADDS",
0,	FMEM,		FESC+4+(0<<11),		"FADDD",
0,	FMEM,		FESC+7+(4<<11),		"FBLD",
0,	FMEM,		FESC+7+(6<<11),		"FBSTP",
0,	FMEM,		FESC+6+(2<<11),		"FICOMS",
0,	FMEM,		FESC+2+(2<<11),		"FICOML",
0,	FMEM,		FESC+0+(2<<11),		"FCOMS",
0,	FMEM,		FESC+4+(2<<11),		"FCOMD",
0,	FMEM,		FESC+6+(3<<11),		"FICOMPS",
0,	FMEM,		FESC+2+(3<<11),		"FICOMPL",
0,	FMEM,		FESC+0+(3<<11),		"FCOMPS",
0,	FMEM,		FESC+4+(3<<11),		"FCOMPD",
0,	FMEM,		FESC+6+(6<<11),		"FIDIVS",
0,	FMEM,		FESC+2+(6<<11),		"FIDIVL",
0,	FMEM,		FESC+0+(6<<11),		"FDIVS",
0,	FMEM,		FESC+4+(6<<11),		"FDIVD",
0,	FMEM,		FESC+6+(7<<11),		"FIDIVRS",
0,	FMEM,		FESC+2+(7<<11),		"FIDIVRL",
0,	FMEM,		FESC+0+(7<<11),		"FDIVRS",
0,	FMEM,		FESC+4+(7<<11),		"FDIVRD",
0,	FMEM,		FESC+7+(5<<11),		"FILDQ",
0,	FMEM,		FESC+7+(0<<11),		"FILDS",
0,	FMEM,		FESC+3+(0<<11),		"FILDL",
0,	FMEM,		FESC+1+(0<<11),		"FLDS",
0,	FMEM,		FESC+5+(0<<11),		"FLDD",
0,	FMEM,		FESC+3+(5<<11),		"FLDX",
0,	FMEM,		FESC+1+(5<<11),		"FLDCW",
0,	FMEM,		FESC+1+(4<<11),		"FLDENV",
0,	FMEM,		FESC+6+(1<<11),		"FIMULS",
0,	FMEM,		FESC+2+(1<<11),		"FIMULL",
0,	FMEM,		FESC+0+(1<<11),		"FMULS",
0,	FMEM,		FESC+4+(1<<11),		"FMULD",
0,	FMEM,		FESC+5+(4<<11),		"FRSTOR",
0,	FMEM,		FESC+5+(6<<11),		"FSAVE",
0,	FMEM,		FESC+7+(2<<11),		"FISTS",
0,	FMEM,		FESC+3+(2<<11),		"FISTL",
0,	FMEM,		FESC+1+(2<<11),		"FSTS",
0,	FMEM,		FESC+5+(2<<11),		"FSTD",
0,	FMEM,		FESC+7+(7<<11),		"FISTPQ",
0,	FMEM,		FESC+7+(3<<11),		"FISTPS",
0,	FMEM,		FESC+3+(3<<11),		"FISTPL",
0,	FMEM,		FESC+1+(3<<11),		"FSTPS",
0,	FMEM,		FESC+5+(3<<11),		"FSTPD",
0,	FMEM,		FESC+3+(7<<11),		"FSTPX",
0,	FMEM,		FESC+1+(7<<11),		"FSTCW",
0,	FMEM,		FESC+1+(6<<11),		"FSTENV",
0,	FMEM,		FESC+5+(7<<11),		"FSTSW",
0,	FMEM,		FESC+6+(4<<11),		"FISUBS",
0,	FMEM,		FESC+2+(4<<11),		"FISUBL",
0,	FMEM,		FESC+0+(4<<11),		"FSUBS",
0,	FMEM,		FESC+4+(4<<11),		"FSUBD",
0,	FMEM,		FESC+6+(5<<11),		"FISUBRS",
0,	FMEM,		FESC+2+(5<<11),		"FISUBRL",
0,	FMEM,		FESC+0+(5<<11),		"FSUBRS",
0,	FMEM,		FESC+4+(5<<11),		"FSUBRD",

0,	FST_I,		FESC+1+(0xC0<<8),	"FLD",
0,	FST_I,		FESC+5+(0xD0<<8),	"FST",
0,	FST_I,		FESC+5+(0xC8<<8),	"FSTP",
0,	FST_I,		FESC+1+(0xC8<<8),	"FXCH",
0,	FST_I,		FESC+0+(0xD0<<8),	"FCOM",
0,	FST_I,		FESC+0+(0xD8<<8),	"FCOMP",
0,	FST_I,		FESC+5+(0xC0<<8),	"FFREE",

0,	FST_ST,		FESC+0+(0xC0<<8),	"FADD",
0,	FST_ST,		FESC+2+(0xC0<<8),	"FADDP",
0,	FST_ST2,	FESC+0+(0xF0<<8),	"FDIV",
0,	FST_ST2,	FESC+2+(0xF0<<8),	"FDIVP",
0,	FST_ST2,	FESC+0+(0xF8<<8),	"FDIVR",
0,	FST_ST2,	FESC+2+(0xF8<<8),	"FDIVRP",
0,	FST_ST,		FESC+0+(0xC8<<8),	"FMUL",
0,	FST_ST,		FESC+2+(0xC8<<8),	"FMULP",
0,	FST_ST2,	FESC+0+(0xE0<<8),	"FSUB",
0,	FST_ST2,	FESC+2+(0xE0<<8),	"FSUBP",
0,	FST_ST2,	FESC+0+(0xE8<<8),	"FSUBR",
0,	FST_ST2,	FESC+2+(0xE8<<8),	"FSUBRP", */

/* 80286 keywords
0,	NOOP_1,		0140,			"PUSHA",
0,	NOOP_1,		0141,			"POPA",
0,	NOOP_1,		0154,			"INSB",
0,	NOOP_1,		0155,			"INS",
0,	NOOP_1,		0155,			"INSW",
0,	NOOP_1,		0156,			"OUTSB",
0,	NOOP_1,		0157,			"OUTS",
0,	NOOP_1,		0157,			"OUTSW",

0,	ARPLOP,		0143,			"ARPL",
0,	ENTER,		0310,			"ENTER",
0,	NOOP_1,		0311,			"LEAVE",
0,	LEAOP,		0142,			"BOUND",

0,	NOOP_2,		017+06<<8,		"CLTS",

0,	EXTOP,		0002,			"LAR",
0,	EXTOP,		0003,			"LSL",

0,	EXTOP1,		0021,			"LGDT",
0,	EXTOP1,		0001,			"SGDT",
0,	EXTOP1,		0031,			"LIDT",
0,	EXTOP1,		0011,			"SIDT",
0,	EXTOP1,		0020,			"LLDT",
0,	EXTOP1,		0000,			"SLDT",
0,	EXTOP1,		0030,			"LTR",
0,	EXTOP1,		0010,			"STR",
0,	EXTOP1,		0061,			"LMSW",
0,	EXTOP1,		0041,			"SMSW",
0,	EXTOP1,		0050,			"VERW",
0,	EXTOP1,		0040,			"VERR", */
