;;; Segment .text (00401000)

;; main: 00401000
main proc
	push	ebp
	mov	ebp,esp
	push	ecx
	fld1
	fstp	dword ptr [esp]
	push	004020C8
	mov	eax,[ebp+08]
	push	eax
	mov	ecx,[ebp+0C]
	mov	edx,[ecx]
	push	edx
	call	00401030
	add	esp,10
	xor	eax,eax
	pop	ebp
	ret
00401024             CC CC CC CC CC CC CC CC CC CC CC CC     ............

;; test1: 00401030
;;   Called from:
;;     00401018 (in main)
;;     00401079 (in test2)
;;     0040109D (in test2)
test1 proc
	push	ebp
	mov	ebp,esp
	fld	dword ptr [ebp+14]
	sub	esp,08
	fstp	double ptr [esp]
	mov	eax,[ebp+10]
	push	eax
	mov	ecx,[ebp+0C]
	push	ecx
	mov	edx,[ebp+08]
	push	edx
	push	004020D0
	call	dword ptr [004020A0]
	add	esp,18
	pop	ebp
	ret
00401058                         CC CC CC CC CC CC CC CC         ........

;; test2: 00401060
test2 proc
	push	ebp
	mov	ebp,esp
	push	ecx
	fld	dword ptr [004020F0]
	fstp	dword ptr [esp]
	push	004020DC
	push	02
	push	004020E0
	call	00401030
	add	esp,10
	cmp	dword ptr [ebp+08],00
	jnz	004010A5

l00401087:
	push	ecx
	fld	dword ptr [004020EC]
	fstp	dword ptr [esp]
	push	004020E4
	push	06
	push	004020E8
	call	00401030
	add	esp,10

l004010A5:
	pop	ebp
	ret
004010A7                      CC CC CC CC CC CC CC CC CC        .........

;; indirect_call_test3: 004010B0
indirect_call_test3 proc
	push	ebp
	mov	ebp,esp
	push	000003E8
	mov	eax,[ebp+08]
	push	eax
	mov	ecx,[ebp+08]
	mov	edx,[ecx]
	mov	eax,[edx+04]
	call	eax
	add	esp,08
	pop	ebp
	ret
004010CB                                  CC CC CC CC CC            .....

;; test4: 004010D0
test4 proc
	push	ebp
	mov	ebp,esp
	mov	eax,[00403018]
	push	eax
	mov	ecx,[00403018]
	mov	edx,[ecx]
	mov	eax,[edx]
	call	eax
	add	esp,04
	pop	ebp
	ret
004010EA                               CC CC CC CC CC CC           ......

;; test5: 004010F0
test5 proc
	push	ebp
	mov	ebp,esp
	push	ecx
	fld	dword ptr [004020F4]
	fstp	dword ptr [esp]
	push	000003E7
	mov	eax,[00403018]
	push	eax
	mov	ecx,[00403018]
	mov	edx,[ecx]
	mov	eax,[edx+04]
	call	eax
	add	esp,0C
	pop	ebp
	ret
0040111A                               CC CC CC CC CC CC           ......

;; test6: 00401120
;;   Called from:
;;     00401218 (in nested_if_blocks_test8)
test6 proc
	push	ebp
	mov	ebp,esp
	push	ecx
	mov	eax,[ebp+10]
	push	eax
	mov	ecx,[ebp+0C]
	push	ecx
	mov	edx,[ebp+08]
	push	edx
	mov	eax,[ebp+08]
	mov	ecx,[eax]
	mov	edx,[ecx+08]
	call	edx
	add	esp,0C
	mov	[ebp-04],eax
	mov	eax,[ebp-04]
	push	eax
	mov	ecx,[ebp+08]
	push	ecx
	mov	edx,[ebp+08]
	mov	eax,[edx]
	mov	ecx,[eax+04]
	call	ecx
	add	esp,08
	mov	esp,ebp
	pop	ebp
	ret
00401159                            CC CC CC CC CC CC CC          .......

;; test7: 00401160
test7 proc
	push	ebp
	mov	ebp,esp
	fld1
	fcomp	double ptr [ebp+08]
	fstsw	ax
	test	ah,05
	jpe	00401189

l0040116F:
	sub	esp,08
	fld	double ptr [ebp+08]
	fstp	double ptr [esp]
	mov	eax,[00403034]
	mov	edx,[eax]
	mov	ecx,[00403034]
	mov	eax,[edx]
	call	eax

l00401189:
	sub	esp,08
	fld	double ptr [ebp+08]
	fstp	double ptr [esp]
	push	0D
	mov	ecx,[00403034]
	mov	edx,[ecx]
	mov	ecx,[00403034]
	mov	eax,[edx+04]
	call	eax
	pop	ebp
	ret
004011A9                            CC CC CC CC CC CC CC          .......

;; nested_if_blocks_test8: 004011B0
;;   Called from:
;;     00401316 (in loop_test11)
nested_if_blocks_test8 proc
	push	ebp
	mov	ebp,esp
	sub	esp,08
	fld	double ptr [ebp+08]
	fstp	double ptr [esp]
	push	FF
	mov	eax,[00403034]
	mov	edx,[eax]
	mov	ecx,[00403034]
	mov	eax,[edx+04]
	call	eax
	fstp	st(0)
	fld	double ptr [00402100]
	fcomp	double ptr [ebp+08]
	fstsw	ax
	test	ah,44
	jpo	0040120D

l004011E2:
	fld	double ptr [004020F8]
	fcomp	double ptr [ebp+08]
	fstsw	ax
	test	ah,41
	jnz	0040120D

l004011F2:
	sub	esp,08
	fld	double ptr [ebp+08]
	fstp	double ptr [esp]
	mov	ecx,[00403034]
	mov	edx,[ecx]
	mov	ecx,[00403034]
	mov	eax,[edx]
	call	eax

l0040120D:
	push	07
	push	06
	mov	ecx,[00403018]
	push	ecx
	call	00401120
	add	esp,0C
	pop	ebp
	ret
00401222       CC CC CC CC CC CC CC CC CC CC CC CC CC CC   ..............

;; loop_test9: 00401230
;;   Called from:
;;     00401303 (in loop_test11)
loop_test9 proc
	push	ebp
	mov	ebp,esp
	sub	esp,0C
	mov	dword ptr [ebp-04],00000000
	jmp	00401248

l0040123F:
	mov	eax,[ebp-04]
	add	eax,01
	mov	[ebp-04],eax

l00401248:
	fild	dword ptr [ebp-04]
	fld	dword ptr [ebp+08]
	sub	esp,08
	fstp	double ptr [esp]
	mov	ecx,[ebp-04]
	push	ecx
	mov	edx,[00403034]
	mov	eax,[edx]
	mov	ecx,[00403034]
	mov	edx,[eax+04]
	fstp	double ptr [ebp-0C]
	call	edx
	fcomp	double ptr [ebp-0C]
	fstsw	ax
	test	ah,41
	jnz	00401294

l00401278:
	fld	dword ptr [ebp+08]
	sub	esp,08
	fstp	double ptr [esp]
	mov	eax,[00403034]
	mov	edx,[eax]
	mov	ecx,[00403034]
	mov	eax,[edx]
	call	eax
	jmp	0040123F

l00401294:
	mov	esp,ebp
	pop	ebp
	ret
00401298                         CC CC CC CC CC CC CC CC         ........

;; const_div_test10: 004012A0
const_div_test10 proc
	push	ebp
	mov	ebp,esp
	mov	eax,0000000A
	mov	ecx,00000003
	mov	edx,[ebp+08]
	test	edx,edx
	jz	004012BA

l004012B4:
	xor	edx,edx
	div	ecx
	mov	ecx,edx

l004012BA:
	mov	[0040302C],ecx
	mov	[00403030],eax
	pop	ebp
	ret
004012C7                      CC CC CC CC CC CC CC CC CC        .........

;; loop_test11: 004012D0
loop_test11 proc
	push	ebp
	mov	ebp,esp
	sub	esp,08
	mov	dword ptr [ebp-04],00000005

l004012DD:
	cmp	dword ptr [ebp-04],00
	jle	00401329

l004012E3:
	mov	eax,[ebp-04]
	and	eax,80000001
	jns	004012F2

l004012ED:
	dec	eax
	or	eax,FE
	inc	eax

l004012F2:
	test	eax,eax
	jnz	0040130D

l004012F6:
	fld	double ptr [ebp+08]
	fstp	dword ptr [ebp-08]
	fld	dword ptr [ebp-08]
	push	ecx
	fstp	dword ptr [esp]
	call	00401230
	add	esp,04
	jmp	0040131E

l0040130D:
	sub	esp,08
	fld	double ptr [ebp+08]
	fstp	double ptr [esp]
	call	004011B0
	add	esp,08

l0040131E:
	mov	ecx,[ebp-04]
	sub	ecx,01
	mov	[ebp-04],ecx
	jmp	004012DD

l00401329:
	mov	esp,ebp
	pop	ebp
	ret
0040132D                                        CC CC CC              ...

;; nested_structs_test12: 00401330
;;   Called from:
;;     00401367 (in nested_structs_test13)
nested_structs_test12 proc
	push	ebp
	mov	ebp,esp
	mov	eax,[ebp+08]
	mov	dword ptr [eax],00000001
	mov	ecx,[ebp+08]
	mov	dword ptr [ecx+04],00000002
	mov	edx,[ebp+08]
	mov	dword ptr [edx+08],00000003
	mov	eax,[ebp+08]
	mov	dword ptr [eax+0C],00000004
	pop	ebp
	ret
0040135C                                     CC CC CC CC             ....

;; nested_structs_test13: 00401360
nested_structs_test13 proc
	push	ebp
	mov	ebp,esp
	mov	eax,[ebp+08]
	push	eax
	call	00401330
	add	esp,04
	pop	ebp
	ret
00401371    CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC  ...............

;; gbl_nested_structs_test14: 00401380
gbl_nested_structs_test14 proc
	push	ebp
	mov	ebp,esp
	mov	dword ptr [0040301C],00000005
	mov	dword ptr [00403020],00000006
	mov	dword ptr [00403024],00000007
	mov	dword ptr [00403028],00000008
	pop	ebp
	ret
004013AD                                        CC CC CC              ...
004013B0 68 85 17 40 00 E8 95 03 00 00 A1 60 30 40 00 C7 h..@.......`0@..
004013C0 04 24 4C 30 40 00 FF 35 5C 30 40 00 A3 4C 30 40 .$L0@..5\0@..L0@
004013D0 00 68 3C 30 40 00 68 40 30 40 00 68 38 30 40 00 .h<0@.h@0@.h80@.
004013E0 FF 15 94 20 40 00 83 C4 14 85 C0 A3 48 30 40 00 ... @.......H0@.
004013F0 7D 08 6A 08 E8 AB 02 00 00 59 C3 6A 10 68 78 21 }.j......Y.j.hx!
00401400 40 00 E8 F1 04 00 00 33 DB 89 5D FC 64 A1 18 00 @......3..].d...
00401410 00 00 8B 70 04 89 5D E4 BF 9C 33 40 00 53 56 57 ...p..]...3@.SVW
00401420 FF 15 24 20 40 00 3B C3 74 19 3B C6 75 08 33 F6 ..$ @.;.t.;.u.3.
00401430 46 89 75 E4 EB 10 68 E8 03 00 00 FF 15 28 20 40 F.u...h......( @
00401440 00 EB DA 33 F6 46 A1 98 33 40 00 3B C6 75 0A 6A ...3.F..3@.;.u.j
00401450 1F E8 4E 02 00 00 59 EB 3B A1 98 33 40 00 85 C0 ..N...Y.;..3@...
00401460 75 2C 89 35 98 33 40 00 68 C0 20 40 00 68 B4 20 u,.5.3@.h. @.h. 
00401470 40 00 E8 7B 04 00 00 59 59 85 C0 74 17 C7 45 FC @..{...YY..t..E.
00401480 FE FF FF FF B8 FF 00 00 00 E9 DD 00 00 00 89 35 ...............5
00401490 54 30 40 00 A1 98 33 40 00 3B C6 75 1B 68 B0 20 T0@...3@.;.u.h. 
004014A0 40 00 68 A8 20 40 00 E8 40 04 00 00 59 59 C7 05 @.h. @..@...YY..
004014B0 98 33 40 00 02 00 00 00 39 5D E4 75 08 53 57 FF .3@.....9].u.SW.
004014C0 15 2C 20 40 00 39 1D A8 33 40 00 74 19 68 A8 33 ., @.9..3@.t.h.3
004014D0 40 00 E8 59 03 00 00 59 85 C0 74 0A 53 6A 02 53 @..Y...Y..t.Sj.S
004014E0 FF 15 A8 33 40 00 A1 3C 30 40 00 8B 0D 80 20 40 ...3@..<0@.... @
004014F0 00 89 01 FF 35 3C 30 40 00 FF 35 40 30 40 00 FF ....5<0@..5@0@..
00401500 35 38 30 40 00 E8 F6 FA FF FF 83 C4 0C A3 50 30 580@..........P0
00401510 40 00 39 1D 44 30 40 00 75 37 50 FF 15 84 20 40 @.9.D0@.u7P... @
00401520 00 8B 45 EC 8B 08 8B 09 89 4D E0 50 51 E8 78 02 ..E......M.PQ.x.
00401530 00 00 59 59 C3 8B 65 E8 8B 45 E0 A3 50 30 40 00 ..YY..e..E..P0@.
00401540 33 DB 39 1D 44 30 40 00 75 07 50 FF 15 8C 20 40 3.9.D0@.u.P... @
00401550 00 39 1D 54 30 40 00 75 06 FF 15 90 20 40 00 C7 .9.T0@.u.... @..
00401560 45 FC FE FF FF FF A1 50 30 40 00 E8 CD 03 00 00 E......P0@......
00401570 C3 66 81 3D 00 00 40 00 4D 5A 74 04 33 C0 EB 4D .f.=..@.MZt.3..M
00401580 A1 3C 00 40 00 8D 80 00 00 40 00 81 38 50 45 00 .<.@.....@..8PE.
00401590 00 75 E9 0F B7 48 18 81 F9 0B 01 00 00 74 1B 81 .u...H.......t..
004015A0 F9 0B 02 00 00 75 D5 83 B8 84 00 00 00 0E 76 CC .....u........v.
004015B0 33 C9 39 88 F8 00 00 00 EB 0E 83 78 74 0E 76 BC 3.9........xt.v.
004015C0 33 C9 39 88 E8 00 00 00 0F 95 C1 8B C1 6A 01 A3 3.9..........j..
004015D0 44 30 40 00 FF 15 40 20 40 00 6A FF FF 15 3C 20 D0@...@ @.j...< 
004015E0 40 00 59 59 A3 A0 33 40 00 A3 A4 33 40 00 FF 15 @.YY..3@...3@...
004015F0 38 20 40 00 8B 0D 68 30 40 00 89 08 FF 15 4C 20 8 @...h0@.....L 
00401600 40 00 8B 0D 64 30 40 00 89 08 A1 6C 20 40 00 8B @...d0@....l @..
00401610 00 A3 94 33 40 00 E8 46 01 00 00 E8 7D 03 00 00 ...3@..F....}...
00401620 83 3D 0C 30 40 00 00 75 0C 68 9D 19 40 00 FF 15 .=.0@..u.h..@...
00401630 70 20 40 00 59 E8 3A 03 00 00 83 3D 08 30 40 00 p @.Y.:....=.0@.
00401640 FF 75 09 6A FF FF 15 74 20 40 00 59 33 C0 C3 E8 .u.j...t @.Y3...
00401650 4C 03 00 00 E9 A2 FD FF FF 8B 44 24 04 8B 00 81 L.........D$....
00401660 38 63 73 6D E0 75 2A 83 78 10 03 75 24 8B 40 14 8csm.u*.x..u$.@.
00401670 3D 20 05 93 19 74 15 3D 21 05 93 19 74 0E 3D 22 = ...t.=!...t.="
00401680 05 93 19 74 07 3D 00 40 99 01 75 05 E8 A3 03 00 ...t.=.@..u.....
00401690 00 33 C0 C2 04 00 68 59 16 40 00 FF 15 20 20 40 .3....hY.@...  @
004016A0 00 33 C0 C3 FF 25 98 20 40 00 6A 14 68 98 21 40 .3...%. @.j.h.!@
004016B0 00 E8 42 02 00 00 FF 35 A4 33 40 00 8B 35 58 20 ..B....5.3@..5X 
004016C0 40 00 FF D6 59 89 45 E4 83 F8 FF 75 0C FF 75 08 @...Y.E....u..u.
004016D0 FF 15 54 20 40 00 59 EB 67 6A 08 E8 66 03 00 00 ..T @.Y.gj..f...
004016E0 59 83 65 FC 00 FF 35 A4 33 40 00 FF D6 89 45 E4 Y.e...5.3@....E.
004016F0 FF 35 A0 33 40 00 FF D6 59 59 89 45 E0 8D 45 E0 .5.3@...YY.E..E.
00401700 50 8D 45 E4 50 FF 75 08 8B 35 3C 20 40 00 FF D6 P.E.P.u..5< @...
00401710 59 50 E8 29 03 00 00 89 45 DC FF 75 E4 FF D6 A3 YP.)....E..u....
00401720 A4 33 40 00 FF 75 E0 FF D6 83 C4 14 A3 A0 33 40 .3@..u........3@
00401730 00 C7 45 FC FE FF FF FF E8 09 00 00 00 8B 45 DC ..E...........E.
00401740 E8 F8 01 00 00 C3 6A 08 E8 ED 02 00 00 59 C3 FF ......j......Y..
00401750 74 24 04 E8 52 FF FF FF F7 D8 1B C0 F7 D8 59 48 t$..R.........YH
00401760 C3 56 57 B8 68 21 40 00 BF 68 21 40 00 3B C7 8B .VW.h!@..h!@.;..
00401770 F0 73 0F 8B 06 85 C0 74 02 FF D0 83 C6 04 3B F7 .s.....t......;.
00401780 72 F1 5F 5E C3 56 57 B8 70 21 40 00 BF 70 21 40 r._^.VW.p!@..p!@
00401790 00 3B C7 8B F0 73 0F 8B 06 85 C0 74 02 FF D0 83 .;...s.....t....
004017A0 C6 04 3B F7 72 F1 5F 5E C3 CC FF 25 88 20 40 00 ..;.r._^...%. @.
004017B0 8B 4C 24 04 66 81 39 4D 5A 74 03 33 C0 C3 8B 41 .L$.f.9MZt.3...A
004017C0 3C 03 C1 81 38 50 45 00 00 75 F0 33 C9 66 81 78 <...8PE..u.3.f.x
004017D0 18 0B 01 0F 94 C1 8B C1 C3 CC CC CC CC CC CC CC ................
004017E0 8B 44 24 04 8B 48 3C 03 C8 0F B7 41 14 53 56 0F .D$..H<....A.SV.
004017F0 B7 71 06 33 D2 85 F6 57 8D 44 08 18 76 1E 8B 7C .q.3...W.D..v..|
00401800 24 14 8B 48 0C 3B F9 72 09 8B 58 08 03 D9 3B FB $..H.;.r..X...;.
00401810 72 0C 83 C2 01 83 C0 28 3B D6 72 E6 33 C0 5F 5E r......(;.r.3._^
00401820 5B C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC [...............
00401830 55 8B EC 6A FE 68 B8 21 40 00 68 51 19 40 00 64 U..j.h.!@.hQ.@.d
00401840 A1 00 00 00 00 50 83 EC 08 53 56 57 A1 10 30 40 .....P...SVW..0@
00401850 00 31 45 F8 33 C5 50 8D 45 F0 64 A3 00 00 00 00 .1E.3.P.E.d.....
00401860 89 65 E8 C7 45 FC 00 00 00 00 68 00 00 40 00 E8 .e..E.....h..@..
00401870 3C FF FF FF 83 C4 04 85 C0 74 55 8B 45 08 2D 00 <........tU.E.-.
00401880 00 40 00 50 68 00 00 40 00 E8 52 FF FF FF 83 C4 .@.Ph..@..R.....
00401890 08 85 C0 74 3B 8B 40 24 C1 E8 1F F7 D0 83 E0 01 ...t;.@$........
004018A0 C7 45 FC FE FF FF FF 8B 4D F0 64 89 0D 00 00 00 .E......M.d.....
004018B0 00 59 5F 5E 5B 8B E5 5D C3 8B 45 EC 8B 08 8B 01 .Y_^[..]..E.....
004018C0 33 D2 3D 05 00 00 C0 0F 94 C2 8B C2 C3 8B 65 E8 3.=...........e.
004018D0 C7 45 FC FE FF FF FF 33 C0 8B 4D F0 64 89 0D 00 .E.....3..M.d...
004018E0 00 00 00 59 5F 5E 5B 8B E5 5D C3 CC FF 25 7C 20 ...Y_^[..]...%| 
004018F0 40 00 FF 25 78 20 40 00 68 51 19 40 00 64 FF 35 @..%x @.hQ.@.d.5
00401900 00 00 00 00 8B 44 24 10 89 6C 24 10 8D 6C 24 10 .....D$..l$..l$.
00401910 2B E0 53 56 57 A1 10 30 40 00 31 45 FC 33 C5 50 +.SVW..0@.1E.3.P
00401920 89 65 E8 FF 75 F8 8B 45 FC C7 45 FC FE FF FF FF .e..u..E..E.....
00401930 89 45 F8 8D 45 F0 64 A3 00 00 00 00 C3 8B 4D F0 .E..E.d.......M.
00401940 64 89 0D 00 00 00 00 59 5F 5F 5E 5B 8B E5 5D 51 d......Y__^[..]Q
00401950 C3 FF 74 24 10 FF 74 24 10 FF 74 24 10 FF 74 24 ..t$..t$..t$..t$
00401960 10 68 4C 1A 40 00 68 10 30 40 00 E8 EC 00 00 00 .hL.@.h.0@......
00401970 83 C4 18 C3 56 68 00 00 03 00 68 00 00 01 00 33 ....Vh....h....3
00401980 F6 56 E8 E1 00 00 00 83 C4 0C 85 C0 74 0D 56 56 .V..........t.VV
00401990 56 56 56 E8 CA 00 00 00 83 C4 14 5E C3 33 C0 C3 VVV........^.3..
004019A0 55 8B EC 83 EC 10 A1 10 30 40 00 83 65 F8 00 83 U.......0@..e...
004019B0 65 FC 00 53 57 BF 4E E6 40 BB 3B C7 BB 00 00 FF e..SW.N.@.;.....
004019C0 FF 74 0D 85 C3 74 09 F7 D0 A3 14 30 40 00 EB 60 .t...t.....0@..`
004019D0 56 8D 45 F8 50 FF 15 0C 20 40 00 8B 75 FC 33 75 V.E.P... @..u.3u
004019E0 F8 FF 15 10 20 40 00 33 F0 FF 15 14 20 40 00 33 .... @.3.... @.3
004019F0 F0 FF 15 18 20 40 00 33 F0 8D 45 F0 50 FF 15 1C .... @.3..E.P...
00401A00 20 40 00 8B 45 F4 33 45 F0 33 F0 3B F7 75 07 BE  @..E.3E.3.;.u..
00401A10 4F E6 40 BB EB 0B 85 F3 75 07 8B C6 C1 E0 10 0B O.@.....u.......
00401A20 F0 89 35 10 30 40 00 F7 D6 89 35 14 30 40 00 5E ..5.0@....5.0@.^
00401A30 5F 5B C9 C3 FF 25 44 20 40 00 FF 25 48 20 40 00 _[...%D @..%H @.
00401A40 FF 25 9C 20 40 00 FF 25 50 20 40 00 3B 0D 10 30 .%. @..%P @.;..0
00401A50 40 00 75 02 F3 C3 E9 13 00 00 00 CC FF 25 5C 20 @.u..........%\ 
00401A60 40 00 FF 25 60 20 40 00 FF 25 64 20 40 00 55 8B @..%` @..%d @.U.
00401A70 EC 81 EC 28 03 00 00 A3 78 31 40 00 89 0D 74 31 ...(....x1@...t1
00401A80 40 00 89 15 70 31 40 00 89 1D 6C 31 40 00 89 35 @...p1@...l1@..5
00401A90 68 31 40 00 89 3D 64 31 40 00 66 8C 15 90 31 40 h1@..=d1@.f...1@
00401AA0 00 66 8C 0D 84 31 40 00 66 8C 1D 60 31 40 00 66 .f...1@.f..`1@.f
00401AB0 8C 05 5C 31 40 00 66 8C 25 58 31 40 00 66 8C 2D ..\1@.f.%X1@.f.-
00401AC0 54 31 40 00 9C 8F 05 88 31 40 00 8B 45 00 A3 7C T1@.....1@..E..|
00401AD0 31 40 00 8B 45 04 A3 80 31 40 00 8D 45 08 A3 8C 1@..E...1@..E...
00401AE0 31 40 00 8B 85 E0 FC FF FF C7 05 C8 30 40 00 01 1@..........0@..
00401AF0 00 01 00 A1 80 31 40 00 A3 7C 30 40 00 C7 05 70 .....1@..|0@...p
00401B00 30 40 00 09 04 00 C0 C7 05 74 30 40 00 01 00 00 0@.......t0@....
00401B10 00 A1 10 30 40 00 89 85 D8 FC FF FF A1 14 30 40 ...0@.........0@
00401B20 00 89 85 DC FC FF FF FF 15 30 20 40 00 A3 C0 30 .........0 @...0
00401B30 40 00 6A 01 E8 39 00 00 00 59 6A 00 FF 15 20 20 @.j..9...Yj...  
00401B40 40 00 68 08 21 40 00 FF 15 00 20 40 00 83 3D C0 @.h.!@.... @..=.
00401B50 30 40 00 00 75 08 6A 01 E8 15 00 00 00 59 68 09 0@..u.j......Yh.
00401B60 04 00 C0 FF 15 04 20 40 00 50 FF 15 08 20 40 00 ...... @.P... @.
00401B70 C9 C3 FF 25 68 20 40 00                         ...%h @.       
