#include <sys/regdef.h>

#define REGLA_30 30
#define REGLA_110 110
#define REGLA_126 126

#define STACK_SIZE 40

/* ABA caller offsets */
#define V_N 56
#define V_R 52
#define V_J 48
#define V_I 44
#define V_A 40

/* SRA offsets */
#define V_SRA_FP 36
#define V_SRA_GP 32

/* LTA offsets */
#define V_LTA_N 28
#define V_LTA_R 24
#define V_LTA_J 20
#define V_LTA_I 16
#define V_LTA_A 12
#define V_LTA_DER 8
#define V_LTA_CEN 4
#define V_LTA_IZQ 0

/* ABA proximo */
/* proximo es hoja no se usa */

.text
.align 2
.globl proximo
.ent proximo

proximo:
		subu sp, sp, STACK_SIZE

		/* SRA */	
		sw fp, V_SRA_FP(sp)
		sw gp, V_SRA_GP(sp)

		move fp, sp
		
		/* ABA Caller */
		sw a0, V_A(fp)
		sw a1, V_I(fp)
		sw a2, V_J(fp)
		sw a3, V_R(fp)
		
		/* LTA */
		lw t0, V_A(fp)
		sw t0, V_LTA_A(fp)

		lw t0, V_I(fp)
		sw t0, V_LTA_I(fp)

		lw t0, V_J(fp)
		sw t0, V_LTA_J(fp)

		lw t0, V_R(fp)
		sw t0, V_LTA_R(fp)

		lw t0, V_N(fp)
		sw t0, V_LTA_N(fp)

indice_izq:
		lw a0, V_LTA_A(fp)			# a0 = a
		lw t0, V_LTA_I(fp)			# t0 = i
		lw t1, V_LTA_N(fp)			# t1 = N
		multu t0, t1				# 
		mflo t0					# t0 = i * N
		lw t2, V_LTA_J(fp)			# t2 = j
		addiu t3, t2, -1			# t3 = j - 1
		div t3, t1				#
		mfhi t3					# t3 = (j - 1) % N
		addu a1, t0, t3				# a1 = t0 + t3
celda_izq:
		addu a1, a0, a1				# Posicion de memoria de celda izq
		lbu a1, 0(a1)				# Valor de celda izq
		sw a1, V_LTA_IZQ			# V_LTA_IZQ = a1

indice_der:	
		addiu t3, t2, 1				# t3 = j + 1
		div t3, t1				#
		mfhi t3					# t3 = (j + 1) % N
		addu a2, t0, t3				# a2 = t0 + t3
celda_der:
		addu a2, a0, a2				# Posicion de memoria de celda izq
		lbu a2, 0(a2)				# Valor de celda izq
		sw a2, V_LTA_DER			# V_LTA_DER = a2

indice_cen:
		addu a3, t0, t2				# a3 = i * N + j
celda_cen:
		addu a3, a0, a3				# Posicion de memoria de celda izq
		lbu a3, 0(a3)				# Valor de celda izq
		sw a3, V_LTA_DER			# V_LTA_CEN = a3

usar_regla_n:
		lw t4, V_LTA_R				# t4 = R
		addiu t5, zero, REGLA_30		# t5 = REGLA_30  
		beq t4, t5, regla_30			# if (t4 == t5) { aplicar regla 30 } else 
		addiu t5, zero, REGLA_126		# t5 = REGLA_126
		beq t4, t5, regla_126 			# if (t4 == t5) { aplicar regla 126 } else
		b regla_110				# regla 110

regla_30:
		or v0, a2, a3				# v0 = D + C, obs se usa notacion de Alg de Boole, + es o, . es and y (+) xor
		xor v0, a1, v0				# v0 = (D + C) (+) I
		b fin_proximo

regla_126:
		not t1, a1 				# t1 = I'
		not t2, a2 				# t2 = D'
		not t3, a3 				# t3 = C'
		and t1, t1, a2				# t1 = I'. D
		and t2, t2, a3				# t2 = D'. C
		and t3, t3, a1				# t3 = C'. I
		or v0, t1, t2				# v0 = I'. D + D'. C
		or v0, v0, t3				# v0 = I'. D + D'. C + C'. I
		b fin_proximo

regla_110:
		xor v0, a2, a3				# v0 = D (+) C
		not t1, a1				# t1 = I'	
		and t2, t1, a2				# t2 = I'. D 
		or v0, v0, t2				# v0 = D (+) C + I'. D
		b fin_proximo

fin_proximo:
    	lw fp, V_SRA_FP(sp)
    	lw gp, V_SRA_GP(sp)     

    	addiu sp, sp, STACK_SIZE
    	jr ra
.end proximo
