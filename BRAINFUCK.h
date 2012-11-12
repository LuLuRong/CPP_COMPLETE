#ifndef BRAINFUCK_H
#define BRAINFUCK_H

/*!
 *  Structure
 *  ---------
 *
 *  IP - Brainfuck instruction pointer
 *  DP - Brainfuck data pointer
 *
 *  IA - Brainfuck instruction array
 *  DA - Brainfuck data  array
 *
 *  X - (IP, DP, IA, DA) - Brainfuck State
 *
 */

/* Check if blank symbol */
#define BF_IS_BLANK(X) JOIN(BF_IS_BLANK_, X) 
#define BF_IS_BLANK_  1
#define BF_IS_BLANK_R 0
#define BF_IS_BLANK_L 0
#define BF_IS_BLANK_U 0
#define BF_IS_BLANK_D 0
#define BF_IS_BLANK_O 0
#define BF_IS_BLANK_F 0
#define BF_IS_BLANK_B 0

/* Check if output symbol */
#define BF_IS_OUTPUT(X) JOIN(BF_IS_OUTPUT_, X)
#define BF_IS_OUTPUT_  0
#define BF_IS_OUTPUT_R 0
#define BF_IS_OUTPUT_L 0
#define BF_IS_OUTPUT_U 0
#define BF_IS_OUTPUT_D 0
#define BF_IS_OUTPUT_O 1
#define BF_IS_OUTPUT_F 0
#define BF_IS_OUTPUT_B 0

/* Check if forward symbol */
#define BF_IS_FORWARD(X) JOIN(BF_IS_FORWARD_, X)
#define BF_IS_FORWARD_  0
#define BF_IS_FORWARD_R 0
#define BF_IS_FORWARD_L 0
#define BF_IS_FORWARD_U 0
#define BF_IS_FORWARD_D 0
#define BF_IS_FORWARD_O 0
#define BF_IS_FORWARD_F 1
#define BF_IS_FORWARD_B 0

/* Check if backward symbol */
#define BF_IS_BACKWARD(X) JOIN(BF_IS_BACKWARD_, X)
#define BF_IS_BACKWARD_  0
#define BF_IS_BACKWARD_R 0
#define BF_IS_BACKWARD_L 0
#define BF_IS_BACKWARD_U 0
#define BF_IS_BACKWARD_D 0
#define BF_IS_BACKWARD_O 0
#define BF_IS_BACKWARD_F 0
#define BF_IS_BACKWARD_B 1

/* Get individual parts */
#define BF_IP(X) FST(X)
#define BF_DP(X) SND(X)
#define BF_IA(X) TRD(X)
#define BF_DA(X) FTH(X)
#define BF_INSTR($, X) NTH($, BF_IA(X), BF_IP(X)) 
#define BF_DATA($, X)  NTH($, BF_DA(X), BF_DP(X))

/* Inc/Dec Data Item */
#define BF_DATA_FST($, X) TAKE($, BF_DA(X), BF_DP(X))
#define BF_DATA_SND($, X) DROP($, BF_DA(X), INC(BF_DP(X)))
#define BF_DATA_INCED($, X) ( INC(NTH($, BF_DA(X), BF_DP(X))) )
#define BF_DATA_DECED($, X) ( DEC(NTH($, BF_DA(X), BF_DP(X))) )

#define BF_DATA_INC($, X) CONCAT( BF_DATA_FST($, X) , CONCAT( BF_DATA_INCED($, X) , BF_DATA_SND($, X) ) )
#define BF_DATA_DEC($, X) CONCAT( BF_DATA_FST($, X) , CONCAT( BF_DATA_DECED($, X) , BF_DATA_SND($, X) ) )

/* Jump Forward/Back */

// TODO: Make count braces
#define BF_JUMP_FWD_C($, X) NOT( BF_IS_BACKWARD(NTH($, FST(X), SND(X))) )
#define BF_JUMP_FWD_M($, X) 
#define BF_JUMP_FWD_U($, X) ( FST(X), INC(SND(X)) )
#define BF_JUMP_FWD_E($, X) INC(SND(X))
#define BF_JUMP_FWD($, X) JOIN(RECR_D, $)(INC($), BF_JUMP_FWD_C, BF_JUMP_FWD_M, BF_JUMP_FWD_U, BF_JUMP_FWD_E, (BF_IA(X), BF_IP(X)) )

// TODO: Make count braces
#define BF_JUMP_BCK_C($, X) NOT( BF_IS_FORWARD(NTH($, FST(X), SND(X))) )
#define BF_JUMP_BCK_M($, X) 
#define BF_JUMP_BCK_U($, X) ( FST(X), DEC(SND(X)) )
#define BF_JUMP_BCK_E($, X) INC(SND(X))
#define BF_JUMP_BCK($, X) JOIN(RECR_D, $)(INC($), BF_JUMP_BCK_C, BF_JUMP_BCK_M, BF_JUMP_BCK_U, BF_JUMP_BCK_E, (BF_IA(X), BF_IP(X)) )

#define BF_JUMP_F($, X) IF_ELSE(NOT(BOOL(BF_DATA($, X))), BF_JUMP_FWD($, X), INC(BF_IP(X)) )
#define BF_JUMP_B($, X) IF_ELSE(BOOL(BF_DATA($, X)), BF_JUMP_BCK($, X) , INC(BF_IP(X)) )

/* Brainfuck Update based on Symbol */
#define BF_UPDATE_SYM($, S, X) JOIN(BF_UPDATE_SYM_, S)($, X)
#define BF_UPDATE_SYM_R($, X) (INC(BF_IP(X)), INC(BF_DP(X)), BF_IA(X), BF_DA(X))
#define BF_UPDATE_SYM_L($, X) (INC(BF_IP(X)), DEC(BF_DP(X)), BF_IA(X), BF_DA(X))
#define BF_UPDATE_SYM_U($, X) (INC(BF_IP(X)), BF_DP(X), BF_IA(X), BF_DATA_INC($, X))
#define BF_UPDATE_SYM_D($, X) (INC(BF_IP(X)), BF_DP(X), BF_IA(X), BF_DATA_DEC($, X))
#define BF_UPDATE_SYM_O($, X) (INC(BF_IP(X)), BF_DP(X), BF_IA(X), BF_DA(X))
#define BF_UPDATE_SYM_F($, X) (BF_JUMP_F($, X),  BF_DP(X), BF_IA(X), BF_DA(X))
#define BF_UPDATE_SYM_B($, X) (BF_JUMP_B($, X),  BF_DP(X), BF_IA(X), BF_DA(X))
#define BF_UPDATE_SYM_($, X) X

/* Main Brainfuck loop */
#define BF_COND($, X) NOT(BF_IS_BLANK(BF_INSTR($, X)))
#define BF_MACRO($, X) IF(BF_IS_OUTPUT(BF_INSTR($, X)), CHAR(BF_DATA($, X)))
#define BF_UPDATE($, X) BF_UPDATE_SYM($, BF_INSTR($, X), X)
#define BF_FINALLY($, X) 
#define BF_RECR($, X) JOIN(RECR_D, $)(INC($), BF_COND, BF_MACRO, BF_UPDATE, BF_FINALLY, X)

/* Extend to get more data cells */
#define BF_DATA_EMPTY() (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)

/* Perform Brainfuck with input I */
#define BRAINFUCK(I) BF_RECR($0, (0, 0, I, BF_DATA_EMPTY()))


#endif