package main

type Command int

const (
	CmdUnknown Command = iota
	CmdMPush
	CmdMInsert
	CmdMGet
	CmdMDel
	CmdMSet
	CmdMLen
	CmdFPushHead
	CmdFPushTail
	CmdFPushAfter
	CmdFPushBefore
	CmdFDelHead
	CmdFDelTail
	CmdFDelAfter
	CmdFDelBefore
	CmdFDelVal
	CmdFGet
	CmdLPushHead
	CmdLPushTail
	CmdLPushAfter
	CmdLPushBefore
	CmdLDelHead
	CmdLDelTail
	CmdLDelAfter
	CmdLDelBefore
	CmdLDelVal
	CmdLGet
	CmdSPush
	CmdSPop
	CmdQPush
	CmdQPop
	CmdTInsert
	CmdTDel
	CmdTGet
	CmdPrint
	CmdHelp
	CmdExit
)

func GetCommand(s string) Command {
	switch s {
	case "MPUSH":
		return CmdMPush
	case "MINSERT":
		return CmdMInsert
	case "MGET":
		return CmdMGet
	case "MDEL":
		return CmdMDel
	case "MSET":
		return CmdMSet
	case "MLEN":
		return CmdMLen
	case "FPUSHHEAD":
		return CmdFPushHead
	case "FPUSHTAIL":
		return CmdFPushTail
	case "FPUSHAFTER":
		return CmdFPushAfter
	case "FPUSHBEFORE":
		return CmdFPushBefore
	case "FDELHEAD":
		return CmdFDelHead
	case "FDELTAIL":
		return CmdFDelTail
	case "FDELAFTER":
		return CmdFDelAfter
	case "FDELBEFORE":
		return CmdFDelBefore
	case "FDELVAL":
		return CmdFDelVal
	case "FGET":
		return CmdFGet
	case "LPUSHHEAD":
		return CmdLPushHead
	case "LPUSHTAIL":
		return CmdLPushTail
	case "LPUSHAFTER":
		return CmdLPushAfter
	case "LPUSHBEFORE":
		return CmdLPushBefore
	case "LDELHEAD":
		return CmdLDelHead
	case "LDELTAIL":
		return CmdLDelTail
	case "LDELAFTER":
		return CmdLDelAfter
	case "LDELBEFORE":
		return CmdLDelBefore
	case "LDELVAL":
		return CmdLDelVal
	case "LGET":
		return CmdLGet
	case "SPUSH":
		return CmdSPush
	case "SPOP":
		return CmdSPop
	case "QPUSH":
		return CmdQPush
	case "QPOP":
		return CmdQPop
	case "TINSERT":
		return CmdTInsert
	case "TDEL":
		return CmdTDel
	case "TGET":
		return CmdTGet
	case "PRINT":
		return CmdPrint
	case "HELP":
		return CmdHelp
	case "EXIT":
		return CmdExit
	}
	return CmdUnknown
}