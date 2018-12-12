
; flat editor core
; Copyright (c) 1999-2015, Tomasz Grysztar.
; All rights reserved.

store_status_for_undo:
	pusha
	test	[editor_mode],FEMODE_NOUNDO
	jnz	undo_disabled
	call	clear_redo_data
	call	allocate_segment
	jc	not_enough_memory
	mov	dword [eax],0
	mov	edi,eax
	xchg	eax,[undo_data]
	push	eax edi
	call	allocate_segment
	pop	edi
	jnc	store_editor_status
	xor	eax,eax
	stosd
	jmp	not_enough_memory
    store_editor_status:
	mov	dword [eax],0
	mov	dword [eax+4],0
	stosd
	pop	eax
	stosd
	lea	esi,[editor_status]
	mov	ecx,editor_status_size shr 2
	rep	movsd
	mov	esi,[lengths_table]
    store_lengths_table:
	call	store_segment_for_undo
	mov	esi,[esi]
	or	esi,esi
	jnz	store_lengths_table
	popa
    store_status_for_undo_ok:
	retn
    undo_disabled:
	call	clear_redo_data
	call	clear_undo_data
	or	[unmodified_state],-1
	popa
	retn

store_segment_for_undo:
	pusha
	or	esi,esi
	jz	segment_for_undo_done
	call	clear_redo_data
	mov	esi,[undo_data]
	or	esi,esi
	jz	segment_for_undo_done
	mov	ebx,[esi]
	mov	eax,[esp+4]
	call	prepare_slot_for_undo_storage
	jc	segment_for_undo_done
	push	edi
	call	allocate_segment
	pop	edi
	mov	ebx,eax
	stosd
	mov	eax,[esp+4]
	stosd
	jc	memory_shortage
	mov	esi,eax
	mov	edi,ebx
	mov	ecx,SEGMENT_LENGTH shr 2
	rep	movsd
    segment_for_undo_done:
	popa
    store_segment_for_undo_ok:
	retn
    prepare_slot_for_undo_storage:
	mov	esi,[undo_data]
	mov	esi,[esi]
	mov	ecx,[esi+4]
	lea	edi,[esi+8]
	repne	scasd
	jne	get_free_slot
	stc
	retn
    get_free_slot:
	mov	ecx,[esi+4]
	lea	edi,[esi+8+ecx*8]
	inc	ecx
	cmp	ecx,SEGMENT_DATA_LENGTH/8
	jbe	slot_ok
	push	esi
	call	allocate_segment
	jc	memory_shortage
	mov	esi,eax
	mov	ebx,[undo_data]
	mov	[ebx],esi
	pop	dword [esi]
	mov	ecx,1
	lea	edi,[esi+8]
    slot_ok:
	mov	[esi+4],ecx
	clc
	retn

store_allocated_segment_for_undo:
	pusha
	call	clear_redo_data
	mov	eax,[esp+1Ch]
	xor	edx,edx
	mov	[eax],edx
	mov	esi,[undo_data]
	or	esi,esi
	jz	segment_for_undo_done
	call	prepare_slot_for_undo_storage
	jc	segment_for_undo_done
	xor	eax,eax
	stosd
	mov	eax,[esp+1Ch]
	stosd
	popa
	retn

store_freed_segment_for_undo:
	pusha
	call	clear_redo_data
	mov	esi,[undo_data]
	or	esi,esi
	jz	segment_for_undo_done
	call	prepare_slot_for_undo_storage
	jc	segment_for_undo_done
	mov	eax,[esp+4]
	stosd
	xor	eax,eax
	stosd
	popa
	retn

undo_changes:
	mov	esi,[undo_data]
	or	esi,esi
	jz	undo_ok
	mov	ebx,[esi]
	mov	eax,[redo_data]
	xchg	eax,[esi+4]
	mov	[undo_data],eax
	mov	[redo_data],esi
	add	esi,8
	lea	edi,[editor_status]
	mov	ecx,editor_status_size shr 2
	call	exchange_data
	xor	edx,edx
    segments_block:
	or	ebx,ebx
	jz	undo_finished
	mov	esi,ebx
	xchg	ebx,edx
	xchg	ebx,[esi]
	add	esi,4
	lodsd
	mov	ecx,eax
	jecxz	undo_finished
	lea	esi,[esi+ecx*8]
    restore_segments:
	sub	esi,8
	push	esi ecx
	mov	edi,[esi+4]
	mov	esi,[esi]
	or	edi,edi
	jz	restore_next
	or	esi,esi
	jz	restore_next
	mov	ecx,SEGMENT_LENGTH shr 2
	call	exchange_data
    restore_next:
	pop	ecx esi
	loop	restore_segments
	jmp	segments_block
    undo_finished:
	mov	esi,[redo_data]
	mov	[esi],edx
    undo_ok:
	retn
    exchange_data:
	mov	eax,[esi]
	xchg	eax,[edi]
	mov	[esi],eax
	add	esi,4
	add	edi,4
	loop	exchange_data
	retn

redo_changes:
	mov	esi,[redo_data]
	or	esi,esi
	jz	redo_ok
	mov	ebx,[esi]
	mov	eax,[undo_data]
	xchg	eax,[esi+4]
	mov	[redo_data],eax
	mov	[undo_data],esi
	add	esi,8
	lea	edi,[editor_status]
	mov	ecx,editor_status_size shr 2
	call	exchange_data
	xor	edx,edx
    redo_segments_block:
	or	ebx,ebx
	jz	redo_finished
	mov	esi,ebx
	xchg	ebx,edx
	xchg	ebx,[esi]
	add	esi,4
	lodsd
	mov	ecx,eax
	jecxz	redo_finished
    redo_segments:
	push	esi ecx
	mov	edi,[esi+4]
	mov	esi,[esi]
	or	edi,edi
	jz	redo_next
	or	esi,esi
	jz	redo_next
	mov	ecx,SEGMENT_LENGTH shr 2
	call	exchange_data
    redo_next:
	pop	ecx esi
	add	esi,8
	loop	redo_segments
	jmp	redo_segments_block
    redo_finished:
	mov	esi,[undo_data]
	mov	[esi],edx
    redo_ok:
	retn

clear_redo_data:
	mov	esi,[redo_data]
	or	esi,esi
	jz	redo_data_ok
    clear_redo_block:
	or	ebx,-1
	xchg	ebx,[esi]
	inc	[released_segments]
	mov	eax,[esi+4]
	mov	[redo_data],eax
    clear_redo_segments:
	or	ebx,ebx
	jz	next_redo_block
	mov	esi,ebx
	or	ebx,-1
	xchg	ebx,[esi]
	inc	[released_segments]
	add	esi,4
	lodsd
	mov	ecx,eax
	jecxz	next_redo_block
    release_redo_segments:
	push	esi ecx
	mov	edi,[esi+4]
	mov	esi,[esi]
	or	edi,edi
	jz	release_next_segment
	or	eax,-1
	or	esi,esi
	jnz	release_data
	xchg	eax,[edi]
	jmp	data_released
    release_data:
	xchg	eax,[esi]
    data_released:
	cmp	eax,-1
	je	release_next_segment
	inc	[released_segments]
    release_next_segment:
	pop	ecx esi
	add	esi,8
	loop	release_redo_segments
	jmp	clear_redo_segments
    next_redo_block:
	mov	esi,[redo_data]
	or	esi,esi
	je	redo_data_ok
	cmp	esi,[unmodified_state]
	jne	clear_redo_block
	mov	[unmodified_state],-1
	jmp	clear_redo_block
    redo_data_ok:
	retn

clear_undo_data:
	mov	esi,[undo_data]
	push	esi
    clear_undo_block:
	or	esi,esi
	jz	undo_data_ok
	or	ebx,-1
	xchg	ebx,[esi]
	inc	[released_segments]
	add	esi,4
	lodsd
	mov	[undo_data],eax
    clear_undo_segments:
	or	ebx,ebx
	jz	next_undo_block
	mov	esi,ebx
	or	ebx,-1
	xchg	ebx,[esi]
	inc	[released_segments]
	add	esi,4
	lodsd
	mov	ecx,eax
	jecxz	next_undo_block
	lea	esi,[esi+ecx*8]
    release_segments:
	sub	esi,8
	mov	edx,[esi]
	or	edx,edx
	jz	release_next
	or	eax,-1
	xchg	[edx],eax
	cmp	eax,-1
	je	release_next
	inc	[released_segments]
    release_next:
	loop	release_segments
    next_undo_block:
	mov	esi,[undo_data]
	cmp	esi,[unmodified_state]
	jne	clear_undo_block
	or	[unmodified_state],-1
	jmp	clear_undo_block
    undo_data_ok:
	pop	esi
	cmp	esi,[unmodified_state]
	jne	unmodified_ok
	mov	[unmodified_state],0
    unmodified_ok:
	retn
