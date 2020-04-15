;;; Segment .text (00401000)

;; main: 00401000
main proc
	push	ebp
	mov	ebp,esp
	push	ecx
	fld1
	fstp	dword ptr [esp]
	push	004020C0
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
	push	004020C8
	call	dword ptr [0040209C]
	add	esp,18
	pop	ebp
	ret
00401058                         CC CC CC CC CC CC CC CC         ........

;; test2: 00401060
test2 proc
	push	ebp
	mov	ebp,esp
	push	ecx
	fld	dword ptr [004020E8]
	fstp	dword ptr [esp]
	push	004020D4
	push	02
	push	004020D8
	call	00401030
	add	esp,10
	cmp	dword ptr [ebp+08],00
	jnz	004010A5

l00401087:
	push	ecx
	fld	dword ptr [004020E4]
	fstp	dword ptr [esp]
	push	004020DC
	push	06
	push	004020E0
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
	fld	dword ptr [004020EC]
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
	mov	eax,[00403024]
	mov	edx,[eax]
	mov	ecx,[00403024]
	mov	eax,[edx]
	call	eax

l00401189:
	sub	esp,08
	fld	double ptr [ebp+08]
	fstp	double ptr [esp]
	push	0D
	mov	ecx,[00403024]
	mov	edx,[ecx]
	mov	ecx,[00403024]
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
	mov	eax,[00403024]
	mov	edx,[eax]
	mov	ecx,[00403024]
	mov	eax,[edx+04]
	call	eax
	fstp	st(0)
	fld	double ptr [004020F8]
	fcomp	double ptr [ebp+08]
	fstsw	ax
	test	ah,44
	jpo	0040120D

l004011E2:
	fld	double ptr [004020F0]
	fcomp	double ptr [ebp+08]
	fstsw	ax
	test	ah,41
	jnz	0040120D

l004011F2:
	sub	esp,08
	fld	double ptr [ebp+08]
	fstp	double ptr [esp]
	mov	ecx,[00403024]
	mov	edx,[ecx]
	mov	ecx,[00403024]
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
	mov	edx,[00403024]
	mov	eax,[edx]
	mov	ecx,[00403024]
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
	mov	eax,[00403024]
	mov	edx,[eax]
	mov	ecx,[00403024]
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
	mov	[0040301C],ecx
	mov	[00403020],eax
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
00401380 68 09 17 40 00 E8 49 03 00 00 A1 4C 30 40 00 C7 h..@..I....L0@..
00401390 04 24 3C 30 40 00 FF 35 48 30 40 00 A3 3C 30 40 .$<0@..5H0@..<0@
004013A0 00 68 2C 30 40 00 68 30 30 40 00 68 28 30 40 00 .h,0@.h00@.h(0@.
004013B0 FF 15 90 20 40 00 83 C4 14 85 C0 A3 38 30 40 00 ... @.......80@.
004013C0 7D 08 6A 08 E8 65 02 00 00 59 C3 6A 10 68 68 21 }.j..e...Y.j.hh!
004013D0 40 00 E8 55 04 00 00 33 DB 89 5D FC 64 A1 18 00 @..U...3..].d...
004013E0 00 00 8B 70 04 89 5D E4 BF 84 33 40 00 53 56 57 ...p..]...3@.SVW
004013F0 FF 15 24 20 40 00 3B C3 74 19 3B C6 75 08 33 F6 ..$ @.;.t.;.u.3.
00401400 46 89 75 E4 EB 10 68 E8 03 00 00 FF 15 28 20 40 F.u...h......( @
00401410 00 EB DA 33 F6 46 A1 80 33 40 00 3B C6 75 0A 6A ...3.F..3@.;.u.j
00401420 1F E8 08 02 00 00 59 EB 3B A1 80 33 40 00 85 C0 ......Y.;..3@...
00401430 75 2C 89 35 80 33 40 00 68 B8 20 40 00 68 B0 20 u,.5.3@.h. @.h. 
00401440 40 00 E8 DD 03 00 00 59 59 85 C0 74 17 C7 45 FC @......YY..t..E.
00401450 FE FF FF FF B8 FF 00 00 00 E9 DD 00 00 00 89 35 ...............5
00401460 44 30 40 00 A1 80 33 40 00 3B C6 75 1B 68 AC 20 D0@...3@.;.u.h. 
00401470 40 00 68 A4 20 40 00 E8 A2 03 00 00 59 59 C7 05 @.h. @......YY..
00401480 80 33 40 00 02 00 00 00 39 5D E4 75 08 53 57 FF .3@.....9].u.SW.
00401490 15 2C 20 40 00 39 1D 90 33 40 00 74 19 68 90 33 ., @.9..3@.t.h.3
004014A0 40 00 E8 0B 03 00 00 59 85 C0 74 0A 53 6A 02 53 @......Y..t.Sj.S
004014B0 FF 15 90 33 40 00 A1 2C 30 40 00 8B 0D 7C 20 40 ...3@..,0@...| @
004014C0 00 89 01 FF 35 2C 30 40 00 FF 35 30 30 40 00 FF ....5,0@..500@..
004014D0 35 28 30 40 00 E8 26 FB FF FF 83 C4 0C A3 40 30 5(0@..&.......@0
004014E0 40 00 39 1D 34 30 40 00 75 37 50 FF 15 80 20 40 @.9.40@.u7P... @
004014F0 00 8B 45 EC 8B 08 8B 09 89 4D E0 50 51 E8 2C 02 ..E......M.PQ.,.
00401500 00 00 59 59 C3 8B 65 E8 8B 45 E0 A3 40 30 40 00 ..YY..e..E..@0@.
00401510 33 DB 39 1D 34 30 40 00 75 07 50 FF 15 88 20 40 3.9.40@.u.P... @
00401520 00 39 1D 44 30 40 00 75 06 FF 15 8C 20 40 00 C7 .9.D0@.u.... @..
00401530 45 FC FE FF FF FF A1 40 30 40 00 E8 31 03 00 00 E......@0@..1...
00401540 C3 66 81 3D 00 00 40 00 4D 5A 74 04 33 C0 EB 51 .f.=..@.MZt.3..Q
00401550 A1 3C 00 40 00 81 B8 00 00 40 00 50 45 00 00 75 .<.@.....@.PE..u
00401560 EB 0F B7 88 18 00 40 00 81 F9 0B 01 00 00 74 1B ......@.......t.
00401570 81 F9 0B 02 00 00 75 D4 83 B8 84 00 40 00 0E 76 ......u.....@..v
00401580 CB 33 C9 39 88 F8 00 40 00 EB 11 83 B8 74 00 40 .3.9...@.....t.@
00401590 00 0E 76 B8 33 C9 39 88 E8 00 40 00 0F 95 C1 8B ..v.3.9...@.....
004015A0 C1 6A 01 A3 34 30 40 00 FF 15 40 20 40 00 6A FF .j..40@...@ @.j.
004015B0 FF 15 3C 20 40 00 59 59 A3 88 33 40 00 A3 8C 33 ..< @.YY..3@...3
004015C0 40 00 FF 15 38 20 40 00 8B 0D 54 30 40 00 89 08 @...8 @...T0@...
004015D0 FF 15 4C 20 40 00 8B 0D 50 30 40 00 89 08 A1 68 ..L @...P0@....h
004015E0 20 40 00 8B 00 A3 7C 33 40 00 E8 F6 00 00 00 E8  @....|3@.......
004015F0 DD 02 00 00 83 3D 0C 30 40 00 00 75 0C 68 D1 18 .....=.0@..u.h..
00401600 40 00 FF 15 6C 20 40 00 59 E8 9A 02 00 00 83 3D @...l @.Y......=
00401610 08 30 40 00 FF 75 09 6A FF FF 15 70 20 40 00 59 .0@..u.j...p @.Y
00401620 33 C0 C3 E8 AC 02 00 00 E9 9E FD FF FF CC FF 25 3..............%
00401630 94 20 40 00 6A 14 68 88 21 40 00 E8 EC 01 00 00 . @.j.h.!@......
00401640 FF 35 8C 33 40 00 8B 35 54 20 40 00 FF D6 59 89 .5.3@..5T @...Y.
00401650 45 E4 83 F8 FF 75 0C FF 75 08 FF 15 50 20 40 00 E....u..u...P @.
00401660 59 EB 61 6A 08 E8 0A 03 00 00 59 83 65 FC 00 FF Y.aj......Y.e...
00401670 35 8C 33 40 00 FF D6 89 45 E4 FF 35 88 33 40 00 5.3@....E..5.3@.
00401680 FF D6 89 45 E0 8D 45 E0 50 8D 45 E4 50 FF 75 08 ...E..E.P.E.P.u.
00401690 E8 D9 02 00 00 89 45 DC FF 75 E4 8B 35 3C 20 40 ......E..u..5< @
004016A0 00 FF D6 A3 8C 33 40 00 FF 75 E0 FF D6 83 C4 1C .....3@..u......
004016B0 A3 88 33 40 00 C7 45 FC FE FF FF FF E8 09 00 00 ..3@..E.........
004016C0 00 8B 45 DC E8 A8 01 00 00 C3 6A 08 E8 97 02 00 ..E.......j.....
004016D0 00 59 C3 FF 74 24 04 E8 58 FF FF FF F7 D8 1B C0 .Y..t$..X.......
004016E0 F7 D8 59 48 C3 56 57 B8 58 21 40 00 BF 58 21 40 ..YH.VW.X!@..X!@
004016F0 00 3B C7 8B F0 73 0F 8B 06 85 C0 74 02 FF D0 83 .;...s.....t....
00401700 C6 04 3B F7 72 F1 5F 5E C3 56 57 B8 60 21 40 00 ..;.r._^.VW.`!@.
00401710 BF 60 21 40 00 3B C7 8B F0 73 0F 8B 06 85 C0 74 .`!@.;...s.....t
00401720 02 FF D0 83 C6 04 3B F7 72 F1 5F 5E C3 CC FF 25 ......;.r._^...%
00401730 84 20 40 00 CC CC CC CC CC CC CC CC CC CC CC CC . @.............
00401740 8B 4C 24 04 66 81 39 4D 5A 74 03 33 C0 C3 8B 41 .L$.f.9MZt.3...A
00401750 3C 03 C1 81 38 50 45 00 00 75 F0 33 C9 66 81 78 <...8PE..u.3.f.x
00401760 18 0B 01 0F 94 C1 8B C1 C3 CC CC CC CC CC CC CC ................
00401770 8B 44 24 04 8B 48 3C 03 C8 0F B7 41 14 53 56 0F .D$..H<....A.SV.
00401780 B7 71 06 33 D2 85 F6 57 8D 44 08 18 76 1E 8B 7C .q.3...W.D..v..|
00401790 24 14 8B 48 0C 3B F9 72 09 8B 58 08 03 D9 3B FB $..H.;.r..X...;.
004017A0 72 0C 83 C2 01 83 C0 28 3B D6 72 E6 33 C0 5F 5E r......(;.r.3._^
004017B0 5B C3 6A 08 68 A8 21 40 00 E8 6E 00 00 00 83 65 [.j.h.!@..n....e
004017C0 FC 00 BA 00 00 40 00 52 E8 73 FF FF FF 59 85 C0 .....@.R.s...Y..
004017D0 74 3D 8B 45 08 2B C2 50 52 E8 92 FF FF FF 59 59 t=.E.+.PR.....YY
004017E0 85 C0 74 2B 8B 40 24 C1 E8 1F F7 D0 83 E0 01 C7 ..t+.@$.........
004017F0 45 FC FE FF FF FF EB 20 8B 45 EC 8B 00 8B 00 33 E...... .E.....3
00401800 C9 3D 05 00 00 C0 0F 94 C1 8B C1 C3 8B 65 E8 C7 .=...........e..
00401810 45 FC FE FF FF FF 33 C0 E8 54 00 00 00 C3 FF 25 E.....3..T.....%
00401820 78 20 40 00 FF 25 74 20 40 00 CC CC 68 85 18 40 x @..%t @...h..@
00401830 00 64 FF 35 00 00 00 00 8B 44 24 10 89 6C 24 10 .d.5.....D$..l$.
00401840 8D 6C 24 10 2B E0 53 56 57 A1 10 30 40 00 31 45 .l$.+.SVW..0@.1E
00401850 FC 33 C5 50 89 65 E8 FF 75 F8 8B 45 FC C7 45 FC .3.P.e..u..E..E.
00401860 FE FF FF FF 89 45 F8 8D 45 F0 64 A3 00 00 00 00 .....E..E.d.....
00401870 C3 8B 4D F0 64 89 0D 00 00 00 00 59 5F 5F 5E 5B ..M.d......Y__^[
00401880 8B E5 5D 51 C3 FF 74 24 10 FF 74 24 10 FF 74 24 ..]Q..t$..t$..t$
00401890 10 FF 74 24 10 68 7A 19 40 00 68 10 30 40 00 E8 ..t$.hz.@.h.0@..
004018A0 E6 00 00 00 83 C4 18 C3 56 68 00 00 03 00 68 00 ........Vh....h.
004018B0 00 01 00 33 F6 56 E8 DB 00 00 00 83 C4 0C 85 C0 ...3.V..........
004018C0 74 0D 56 56 56 56 56 E8 C4 00 00 00 83 C4 14 5E t.VVVVV........^
004018D0 C3 33 C0 C3 55 8B EC 83 EC 10 A1 10 30 40 00 83 .3..U.......0@..
004018E0 65 F8 00 83 65 FC 00 53 57 BF 4E E6 40 BB 3B C7 e...e..SW.N.@.;.
004018F0 BB 00 00 FF FF 74 0D 85 C3 74 09 F7 D0 A3 14 30 .....t...t.....0
00401900 40 00 EB 60 56 8D 45 F8 50 FF 15 10 20 40 00 8B @..`V.E.P... @..
00401910 75 FC 33 75 F8 FF 15 14 20 40 00 33 F0 FF 15 18 u.3u.... @.3....
00401920 20 40 00 33 F0 FF 15 1C 20 40 00 33 F0 8D 45 F0  @.3.... @.3..E.
00401930 50 FF 15 20 20 40 00 8B 45 F4 33 45 F0 33 F0 3B P..  @..E.3E.3.;
00401940 F7 75 07 BE 4F E6 40 BB EB 0B 85 F3 75 07 8B C6 .u..O.@.....u...
00401950 C1 E0 10 0B F0 89 35 10 30 40 00 F7 D6 89 35 14 ......5.0@....5.
00401960 30 40 00 5E 5F 5B C9 C3 FF 25 44 20 40 00 FF 25 0@.^_[...%D @..%
00401970 48 20 40 00 FF 25 98 20 40 00 3B 0D 10 30 40 00 H @..%. @.;..0@.
00401980 75 02 F3 C3 E9 13 00 00 00 CC FF 25 58 20 40 00 u..........%X @.
00401990 FF 25 5C 20 40 00 FF 25 60 20 40 00 55 8B EC 81 .%\ @..%` @.U...
004019A0 EC 28 03 00 00 A3 60 31 40 00 89 0D 5C 31 40 00 .(....`1@...\1@.
004019B0 89 15 58 31 40 00 89 1D 54 31 40 00 89 35 50 31 ..X1@...T1@..5P1
004019C0 40 00 89 3D 4C 31 40 00 66 8C 15 78 31 40 00 66 @..=L1@.f..x1@.f
004019D0 8C 0D 6C 31 40 00 66 8C 1D 48 31 40 00 66 8C 05 ..l1@.f..H1@.f..
004019E0 44 31 40 00 66 8C 25 40 31 40 00 66 8C 2D 3C 31 D1@.f.%@1@.f.-<1
004019F0 40 00 9C 8F 05 70 31 40 00 8B 45 00 A3 64 31 40 @....p1@..E..d1@
00401A00 00 8B 45 04 A3 68 31 40 00 8D 45 08 A3 74 31 40 ..E..h1@..E..t1@
00401A10 00 8B 85 E0 FC FF FF C7 05 B0 30 40 00 01 00 01 ..........0@....
00401A20 00 A1 68 31 40 00 A3 64 30 40 00 C7 05 58 30 40 ..h1@..d0@...X0@
00401A30 00 09 04 00 C0 C7 05 5C 30 40 00 01 00 00 00 A1 .......\0@......
00401A40 10 30 40 00 89 85 D8 FC FF FF A1 14 30 40 00 89 .0@.........0@..
00401A50 85 DC FC FF FF FF 15 30 20 40 00 A3 A8 30 40 00 .......0 @...0@.
00401A60 6A 01 E8 39 00 00 00 59 6A 00 FF 15 00 20 40 00 j..9...Yj.... @.
00401A70 68 00 21 40 00 FF 15 04 20 40 00 83 3D A8 30 40 h.!@.... @..=.0@
00401A80 00 00 75 08 6A 01 E8 15 00 00 00 59 68 09 04 00 ..u.j......Yh...
00401A90 C0 FF 15 08 20 40 00 50 FF 15 0C 20 40 00 C9 C3 .... @.P... @...
00401AA0 FF 25 64 20 40 00                               .%d @.         