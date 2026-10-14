#include "commands.h"

Command GetCommand(const string& str) {
    if (str == "MPUSH") return Command::MPUSH;
    if (str == "MINSERT") return Command::MINSERT;
    if (str == "MGET") return Command::MGET;
    if (str == "MDEL") return Command::MDEL;
    if (str == "MSET") return Command::MSET;
    if (str == "MLEN") return Command::MLEN;
    if (str == "FPUSHHEAD") return Command::FPUSHHEAD;
    if (str == "FPUSHTAIL") return Command::FPUSHTAIL;
    if (str == "FPUSHAFTER") return Command::FPUSHAFTER;
    if (str == "FPUSHBEFORE") return Command::FPUSHBEFORE;
    if (str == "FDELHEAD") return Command::FDELHEAD;
    if (str == "FDELTAIL") return Command::FDELTAIL;
    if (str == "FDELAFTER") return Command::FDELAFTER;
    if (str == "FDELBEFORE") return Command::FDELBEFORE;
    if (str == "FDELVAL") return Command::FDELVAL;
    if (str == "FGET") return Command::FGET;
    if (str == "LPUSHHEAD") return Command::LPUSHHEAD;
    if (str == "LPUSHTAIL") return Command::LPUSHTAIL;
    if (str == "LPUSHAFTER") return Command::LPUSHAFTER;
    if (str == "LPUSHBEFORE") return Command::LPUSHBEFORE;
    if (str == "LDELHEAD") return Command::LDELHEAD;
    if (str == "LDELTAIL") return Command::LDELTAIL;
    if (str == "LDELAFTER") return Command::LDELAFTER;
    if (str == "LDELBEFORE") return Command::LDELBEFORE;
    if (str == "LDELVAL") return Command::LDELVAL;
    if (str == "LGET") return Command::LGET;
    if (str == "SPUSH") return Command::SPUSH;
    if (str == "SPOP") return Command::SPOP;
    if (str == "QPUSH") return Command::QPUSH;
    if (str == "QPOP") return Command::QPOP;
    if (str == "TINSERT") return Command::TINSERT;
    if (str == "TDEL") return Command::TDEL;
    if (str == "TGET") return Command::TGET;
    if (str == "PRINT") return Command::PRINT;
    if (str == "HELP") return Command::HELP;
    if (str == "EXIT") return Command::EXIT;
    return Command::UNKNOWN;
}
