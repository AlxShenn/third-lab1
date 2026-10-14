package main

type Command int

const (
	MPUSH Command = iota
	MINSERT
	MGET
	MDEL
	MSET
	MLEN
	FPUSHHEAD
	FPUSHTAIL
	FPUSHAFTER
	FPUSHBEFORE
	FDELHEAD
	FDELTAIL
	FDELAFTER
	FDELBEFORE
	FDELVAL
	FGET
	LPUSHHEAD
	LPUSHTAIL
	LPUSHAFTER
	LPUSHBEFORE
	LDELHEAD
	LDELTAIL
	LDELAFTER
	LDELBEFORE
	LDELVAL
	LGET
	SPUSH
	SPOP
	QPUSH
	QPOP
	TINSERT
	TDEL
	TGET
	PRINT
	HELP
	EXIT
	UNKNOWN
)

func GetCommand(str string) Command {
	switch str {
	case "MPUSH":
		return MPUSH
	case "MINSERT":
		return MINSERT
	case "MGET":
		return MGET
	case "MDEL":
		return MDEL
	case "MSET":
		return MSET
	case "MLEN":
		return MLEN
	case "FPUSHHEAD":
		return FPUSHHEAD
	case "FPUSHTAIL":
		return FPUSHTAIL
	case "FPUSHAFTER":
		return FPUSHAFTER
	case "FPUSHBEFORE":
		return FPUSHBEFORE
	case "FDELHEAD":
		return FDELHEAD
	case "FDELTAIL":
		return FDELTAIL
	case "FDELAFTER":
		return FDELAFTER
	case "FDELBEFORE":
		return FDELBEFORE
	case "FDELVAL":
		return FDELVAL
	case "FGET":
		return FGET
	case "LPUSHHEAD":
		return LPUSHHEAD
	case "LPUSHTAIL":
		return LPUSHTAIL
	case "LPUSHAFTER":
		return LPUSHAFTER
	case "LPUSHBEFORE":
		return LPUSHBEFORE
	case "LDELHEAD":
		return LDELHEAD
	case "LDELTAIL":
		return LDELTAIL
	case "LDELAFTER":
		return LDELAFTER
	case "LDELBEFORE":
		return LDELBEFORE
	case "LDELVAL":
		return LDELVAL
	case "LGET":
		return LGET
	case "SPUSH":
		return SPUSH
	case "SPOP":
		return SPOP
	case "QPUSH":
		return QPUSH
	case "QPOP":
		return QPOP
	case "TINSERT":
		return TINSERT
	case "TDEL":
		return TDEL
	case "TGET":
		return TGET
	case "PRINT":
		return PRINT
	case "HELP":
		return HELP
	case "EXIT":
		return EXIT
	}
	return UNKNOWN
}
