.name "champzer"
.comment "blbllblb"

	sti r1, %:live, %1
	ld %0, r10

live:	live %1
		zjmp %:live
