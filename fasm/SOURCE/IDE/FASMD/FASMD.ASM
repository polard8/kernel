
; flat assembler IDE for DOS/DPMI
; Copyright (c) 1999-2018, Tomasz Grysztar.
; All rights reserved.

	format	MZ
	heap	0
	stack	stack_segment:stack_top-stack_bottom
	entry	loader:init

segment loader use16

init:

	mov	ax,3301h
	xor	dl,dl
	int	21h
	push	ds cs
	pop	ds
	mov	ax,2524h
	mov	dx,dos_error_handler
	int	21h
	pop	ds

	mov	ax,1A00h
	xor	bx,bx
	int	10h
	cmp	al,1Ah
	jne	short no_vga
	cmp	bl,8
	jne	short no_vga

	mov	ax,1687h
	int	2Fh
	or	ax,ax			; DPMI installed?
	jnz	short no_dpmi
	test	bl,1			; 32-bit programs supported?
	jz	short no_dpmi
	mov	word [cs:mode_switch],di
	mov	word [cs:mode_switch+2],es
	mov	bx,si			; allocate memory for DPMI data
	mov	ah,48h
	int	21h
	jnc	switch_to_protected_mode
  init_failed:
	call	init_error
	db	'DPMI initialization failed.',0Dh,0Ah,0
  no_vga:
	call	init_error
	db	'Color VGA adapter is required.',0Dh,0Ah,0
  no_dpmi:
	call	init_error
	db	'32-bit DPMI services are not available.',0Dh,0Ah,0
  init_error:
	pop	si
	push	cs
	pop	ds
      display_error:
	lodsb
	test	al,al
	jz	short error_finish
	mov	dl,al
	mov	ah,2
	int	21h
	jmp	short display_error
      error_finish:
	mov	ax,4CFFh
	int	21h
  dos_error_handler:
	mov	al,3
	iret
  switch_to_protected_mode:
	mov	es,ax
	mov	ds,[ds:2Ch]
	mov	ax,1
	call	far [cs:mode_switch]	; switch to protected mode
	jc	init_failed
	mov	cx,1
	xor	ax,ax
	int	31h			; allocate descriptor for code
	jc	init_failed
	mov	si,ax
	xor	ax,ax
	int	31h			; allocate descriptor for data
	jc	init_failed
	mov	di,ax
	mov	dx,cs
	lar	cx,dx
	shr	cx,8
	or	cx,0C000h
	mov	bx,si
	mov	ax,9
	int	31h			; set code descriptor access rights
	jc	init_failed
	mov	dx,ds
	lar	cx,dx
	shr	cx,8
	or	cx,0C000h
	mov	bx,di
	int	31h			; set data descriptor access rights
	jc	init_failed
	mov	ecx,main
	shl	ecx,4
	mov	dx,cx
	shr	ecx,16
	mov	ax,7
	int	31h			; set data descriptor base address
	jc	init_failed
	mov	bx,si
	int	31h			; set code descriptor base address
	jc	init_failed
	mov	cx,0FFFFh
	mov	dx,0FFFFh
	mov	ax,8			; set segment limit to 4 GB
	int	31h
	jc	init_failed
	mov	bx,di
	int	31h
	jc	init_failed
	mov	ax,ds
	mov	ds,di
	mov	[main_selector],di
	mov	[psp_selector],es
	mov	[environment_selector],ax
	cli
	mov	ss,di
	mov	esp,stack_top
	sti
	mov	es,di
	mov	cx,1
	xor	ax,ax
	int	31h			; allocate descriptor for BIOS data segment
	jc	init_failed
	mov	bx,ax
	lar	cx,[environment_selector]
	shr	cx,8
	mov	ax,9
	int	31h			; set descriptor access rights
	jc	init_failed
	xor	cx,cx
	mov	dx,400h
	mov	ax,7
	int	31h			; set base address of BIOS data segment
	jc	init_failed
	xor	cx,cx
	mov	dx,0FFh
	mov	ax,8
	int	31h			; set limit of BIOS data segment
	jc	init_failed
	mov	fs,bx
	mov	[bios_selector],bx
	mov	cx,1
	xor	ax,ax
	int	31h			; allocate descriptor for video segment
	jc	init_failed
	mov	bx,ax
	lar	cx,[environment_selector]
	shr	cx,8
	mov	ax,9
	int	31h			; set descriptor access rights
	jc	init_failed
	mov	cx,0Bh
	mov	dx,8000h
	mov	ax,7
	int	31h			; set base address of video segment
	jc	init_failed
	xor	cx,cx
	mov	dx,4000-1
	mov	ax,8
	int	31h			; set limit of video segment
	jc	init_failed
	mov	gs,bx
	mov	[video_selector],bx
	push	si
	push	start
	retf

  mode_switch dd ?

segment main use32

  start:
	cld

	call	init_video
	jc	startup_failed

	call	init_editor_memory
	jc	startup_failed

	xor	eax,eax
	mov	[next_instance],eax
	mov	[previous_instance],eax
	mov	[file_path],eax

	mov	ecx,1000h
	mov	[line_buffer_size],ecx
	call	get_memory
	or	eax,eax
	jz	startup_failed
	mov	[line_buffer],eax
	mov	[line_buffer_handle],ebx

	mov	[stack_limit],stack_bottom

	mov	edi,upper_case_table
	xor	al,al
	mov	ecx,80h
      prepare_case_table:
	stosb
	inc	al
	loop	prepare_case_table
      make_extended_case_table:
	push	eax
	mov	dl,al
	mov	ax,6520h
	int	21h
	mov	al,[esp]
	jc	upper_case_character_ok
	mov	al,dl
      upper_case_character_ok:
	stosb
	pop	eax
	inc	al
	jnz	make_extended_case_table
	mov	esi,upper_case_table+'A'
	mov	edi,upper_case_table+'a'
	mov	ecx,26
	rep	movsb
	xor	al,al
	mov	edi,lower_case_table
      prepare_lower_case_table:
	stosb
	inc	al
	jnz	prepare_lower_case_table
	mov	esi,lower_case_table+'a'
	mov	edi,lower_case_table+'A'
	mov	ecx,26
	rep	movsb
	mov	eax,80h
	xor	edx,edx
      make_lower_case_table:
	mov	dl,[upper_case_table+eax]
	cmp	al,dl
	je	lower_case_character_ok
	cmp	dl,80h
	jb	lower_case_character_ok
	mov	[lower_case_table+edx],al
      lower_case_character_ok:
	inc	al
	jnz	make_lower_case_table
	mov	edi,characters
	xor	al,al
      prepare_characters_table:
	stosb
	inc	al
	jnz	prepare_characters_table
	mov	esi,characters+'a'
	mov	edi,characters+'A'
	mov	ecx,26
	rep	movsb
	mov	edi,characters
	mov	esi,symbol_characters+1
	movzx	ecx,byte [esi-1]
	xor	eax,eax
      convert_table:
	lodsb
	mov	byte [edi+eax],0
	loop	convert_table
	mov	[selected_character],'p'

	call	get_low_memory

	push	ds
	mov	ds,[environment_selector]
	xor	esi,esi
	mov	edi,ini_path
      skip_environment:
	lodsb
	test	al,al
	jnz	skip_environment
	lodsb
	test	al,al
	jnz	skip_environment
	add	esi,2
      copy_program_path:
	lodsb
	stosb
	test	al,al
	jnz	copy_program_path
	pop	ds
	dec	edi
	mov	edx,edi
      find_extension_start:
	cmp	edi,ini_path
	je	attach_extension
	cmp	byte [edi-1],'.'
	je	replace_extension
	cmp	byte [edi-1],'/'
	je	attach_extension
	dec	edi
	jmp	find_extension_start
      attach_extension:
	mov	edi,edx
	mov	al,'.'
	stosb
      replace_extension:
	mov	ecx,edi
	mov	eax,'INI'
	stosd

	xor	eax,eax
	mov	[ini_data],eax
	mov	[main_project_file],eax
	mov	[clipboard],eax
	mov	[current_operation],al
	mov	[find_flags],eax
	mov	[command_flags],al

	call	load_configuration

	call	update_positions
	call	switch_to_ide_screen

	mov	esi,81h
      process_arguments:
	push	ds
	mov	ds,[psp_selector]
	mov	edi,filename_buffer
      find_argument:
	lodsb
	cmp	al,20h
	je	find_argument
	cmp	al,9
	je	find_argument
	cmp	al,22h
	je	quoted_argument
	dec	esi
      copy_argument:
	lodsb
	cmp	al,20h
	je	argument_end
	cmp	al,9
	je	argument_end
	cmp	al,0Dh
	je	argument_end
	stosb
	jmp	copy_argument
      quoted_argument:
	lodsb
	cmp	al,0Dh
	je	argument_end
	stosb
	cmp	al,22h
	jne	quoted_argument
	lodsb
	cmp	al,22h
	je	quoted_argument
	dec	edi
      argument_end:
	dec	esi
	pop	ds
	cmp	edi,filename_buffer
	je	main_loop
	xor	al,al
	stosb
	push	esi
	mov	edx,filename_buffer
	call	load_file
	pop	esi
	jmp	process_arguments

  main_loop:

	call	update_cursor
	call	update_screen

	xor	al,al
	xchg	[current_operation],al
	mov	[last_operation],al
	mov	[was_selection],1
	mov	eax,[selection_line]
	or	eax,eax
	jz	no_selection
	cmp	eax,[caret_line]
	jne	get_command
	mov	eax,[selection_position]
	cmp	eax,[caret_position]
	jne	get_command
    no_selection:
	mov	[was_selection],0
	mov	eax,[caret_line]
	mov	[selection_line],eax
	mov	eax,[caret_position]
	mov	[selection_position],eax
	mov	eax,[caret_line_number]
	mov	[selection_line_number],eax
    get_command:
	call	wait_for_input
	cmp	ah,1
	je	close_editor
	jb	character
	cmp	al,0Eh
	je	new_editor
	cmp	ah,94h
	je	switch_editor
	cmp	ah,0A5h
	je	switch_editor
	cmp	ah,3Ch
	je	save_current
	cmp	ah,55h
	je	save_as
	cmp	ah,3Eh
	je	open_file
	cmp	ah,3Fh
	je	goto
	cmp	ah,41h
	je	search
	cmp	ah,5Ah
	je	search_next
	cmp	ah,64h
	je	replace
	cmp	ah,43h
	je	compile_and_run
	cmp	ah,66h
	je	compile
	cmp	ah,65h
	je	build_symbols
	cmp	ah,5Ch
	je	assign_to_compiler
	cmp	ah,63h
	je	calculator
	cmp	ah,6Ch
	je	show_user_screen
	cmp	ah,44h
	je	options
	cmp	ah,3Dh
	je	search_next
	test	byte [fs:17h],1000b
	jz	no_alt
	cmp	ah,2Dh
	je	close_all
	cmp	ah,0Eh
	je	undo
	cmp	ah,0A3h
	je	disable_undo
	cmp	ah,98h
	je	scroll_up
	cmp	ah,0A0h
	je	scroll_down
	cmp	ah,9Bh
	je	scroll_left
	cmp	ah,9Dh
	je	scroll_right
      no_alt:
	or	al,al
	jz	no_ascii
	cmp	al,0E0h
	jne	ascii
      no_ascii:
	cmp	ah,4Bh
	je	left_key
	cmp	ah,4Dh
	je	right_key
	cmp	ah,48h
	je	up_key
	cmp	ah,50h
	je	down_key
	cmp	ah,47h
	je	home_key
	cmp	ah,4Fh
	je	end_key
	cmp	ah,77h
	je	screen_home
	cmp	ah,75h
	je	screen_end
	cmp	ah,73h
	je	word_left
	cmp	ah,74h
	je	word_right
	cmp	ah,8Dh
	je	word_left
	cmp	ah,91h
	je	word_right
	cmp	ah,49h
	je	pgup_key
	cmp	ah,51h
	je	pgdn_key
	cmp	ah,84h
	je	text_home
	cmp	ah,76h
	je	text_end
	cmp	ah,52h
	je	ins_key
	cmp	ah,0A2h
	je	switch_blocks
	cmp	ah,40h
	je	f6_key
	cmp	ah,93h
	je	block_delete
	cmp	ah,92h
	je	block_copy
	cmp	ah,53h
	je	del_key
	cmp	ah,78h
	jb	get_command
	cmp	ah,80h
	ja	get_command
	sub	ah,77h
	movzx	ecx,ah
	jmp	select_editor
      ascii:
	cmp	al,7Fh
	je	word_back
	cmp	al,20h
	jae	character
	cmp	al,8
	je	backspace_key
	cmp	al,9
	je	tab_key
	cmp	al,0Dh
	je	enter_key
	cmp	al,19h
	je	ctrl_y_key
	cmp	al,1Ah
	je	undo
	cmp	al,18h
	je	block_cut
	cmp	al,3
	je	block_copy
	cmp	al,16h
	je	block_paste
	cmp	al,0Fh
	je	open_file
	cmp	al,13h
	je	save_current
	cmp	al,6
	je	search
	cmp	al,7
	je	goto
	cmp	al,1
	je	select_all
	cmp	al,2
	je	ascii_table
	jmp	get_command
  character:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	cmp	[was_selection],0
	je	no_selection_to_replace
	call	store_status_for_undo
	test	[editor_style],FES_SECURESEL
	jnz	character_undo_ok
	push	eax
	call	delete_block
	pop	eax
	call	put_character
	call	finish_edit
	mov	[selection_line],0
	jmp	text_modified
    no_selection_to_replace:
	mov	[current_operation],20h
	cmp	[last_operation],20h
	jne	character_undopoint
	mov	edx,[unmodified_state]
	cmp	edx,[undo_data]
	jne	character_undo_ok
	or	[unmodified_state],-1
	jmp	character_undo_ok
    character_undopoint:
	call	store_status_for_undo
    character_undo_ok:
	call	put_character
	call	finish_edit
	mov	[selection_line],0
	jmp	text_modified
  tab_key:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	call	store_status_for_undo
	cmp	[was_selection],0
	je	tab_securesel
	test	[editor_style],FES_SECURESEL
	jnz	tab_securesel
	call	delete_block
    tab_securesel:
	call	tabulate
	mov	[selection_line],0
	call	finish_edit
	jmp	text_modified
  enter_key:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	call	store_status_for_undo
	cmp	[was_selection],0
	je	enter_secureselection_ok
	test	[editor_style],FES_SECURESEL
	jnz	enter_secureselection_ok
	call	delete_block
    enter_secureselection_ok:
	call	carriage_return
	mov	[selection_line],0
	test	[editor_mode],FEMODE_OVERWRITE
	jnz	text_modified
	call	finish_edit
	jmp	text_modified
  backspace_key:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	test	byte [fs:17h],100b
	jnz	replace
	cmp	[was_selection],0
	je	no_selection_to_clear
	test	[editor_style],FES_SECURESEL
	jz	block_delete
    no_selection_to_clear:
	cmp	[caret_position],0
	je	line_back
	mov	[current_operation],8
	cmp	[last_operation],8
	jne	backspace_undopoint
	mov	edx,[unmodified_state]
	cmp	edx,[undo_data]
	jne	undo_back_ok
	or	[unmodified_state],-1
	jmp	undo_back_ok
    backspace_undopoint:
	call	store_status_for_undo
    undo_back_ok:
	dec	[caret_position]
	call	delete_character
	call	finish_edit
	mov	[selection_line],0
	jmp	text_modified
    line_back:
	test	[editor_mode],FEMODE_OVERWRITE
	jnz	get_command
	mov	esi,[caret_line]
	mov	esi,[esi+4]
	or	esi,esi
	jz	get_command
	call	store_status_for_undo
	mov	[caret_line],esi
	dec	[caret_line_number]
	call	check_line_length
	mov	[caret_position],ecx
	call	cut_line_break
	call	finish_edit
	mov	[selection_line],0
	jmp	text_modified
    word_back:
	call	store_status_for_undo
	push	[caret_position]
	mov	esi,[caret_line]
	xor	eax,eax
	xchg	eax,[esi+4]
	push	eax
	call	move_to_previous_word
	pop	eax
	mov	esi,[caret_line]
	mov	[esi+4],eax
	pop	ecx
	sub	ecx,[caret_position]
	call	delete_from_line
	call	finish_edit
	jmp	text_modified
  del_key:
	test	byte [fs:17h],11b
	jnz	block_cut
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	cmp	[was_selection],0
	je	no_selection_on_del
	test	[editor_style],FES_SECURESEL
	jz	block_delete
    no_selection_on_del:
	mov	esi,[caret_line]
	test	[editor_mode],FEMODE_OVERWRITE
	jnz	delete_char
	call	check_line_length
	cmp	ecx,[caret_position]
	ja	delete_char
	cmp	dword [esi],0
	je	get_command
	call	store_status_for_undo
	call	cut_line_break
	call	finish_edit
	mov	[selection_line],0
	jmp	text_modified
    delete_char:
	mov	[current_operation],0E0h
	cmp	[last_operation],0E0h
	je	undo_delete_ok
	call	store_status_for_undo
    undo_delete_ok:
	call	delete_character
	call	finish_edit
	mov	[selection_line],0
	jmp	text_modified
  ctrl_y_key:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	call	store_status_for_undo
	call	remove_line
	jmp	text_modified
  f6_key:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	call	store_status_for_undo
	call	duplicate_line
	jmp	text_modified
  left_key:
	cmp	[caret_position],0
	jle	text_modified
	dec	[caret_position]
	jmp	moved_caret
  right_key:
	mov	eax,[caret_position]
	cmp	eax,[maximum_position]
	jae	text_modified
	inc	[caret_position]
	jmp	moved_caret
  up_key:
	call	move_line_up
	jmp	moved_caret
  down_key:
	call	move_line_down
	jmp	moved_caret
  home_key:
	mov	[caret_position],0
	jmp	moved_caret
  end_key:
	call	move_to_line_end
	jmp	moved_caret
  screen_home:
	mov	eax,[window_line]
	mov	[caret_line],eax
	mov	eax,[window_line_number]
	mov	[caret_line_number],eax
	jmp	moved_caret
  screen_end:
	mov	eax,[window_line_number]
	add	eax,[window_height]
	dec	eax
	call	find_line
	mov	[caret_line],esi
	mov	[caret_line_number],ecx
	jmp	moved_caret
  pgup_key:
	call	move_page_up
	jmp	moved_caret
  pgdn_key:
	call	move_page_down
	jmp	moved_caret
  text_home:
	mov	eax,[first_line]
	mov	[caret_line],eax
	mov	[caret_line_number],1
	jmp	moved_caret
  text_end:
	or	eax,-1
	call	find_line
	mov	[caret_line],esi
	mov	[caret_line_number],ecx
	jmp	moved_caret
  word_left:
	call	move_to_previous_word
	jmp	moved_caret
  word_right:
	call	get_caret_segment
	call	move_to_next_word
	jmp	moved_caret
  scroll_left:
	cmp	[window_position],0
	je	main_loop
	dec	[window_position]
	jmp	moved_window
  scroll_right:
	inc	[window_position]
	jmp	moved_window
  scroll_up:
	mov	esi,[window_line]
	mov	esi,[esi+4]
	or	esi,esi
	jz	main_loop
	mov	[window_line],esi
	dec	[window_line_number]
	jmp	moved_window
  scroll_down:
	mov	esi,[window_line]
      find_next_window_line:
	mov	esi,[esi]
	btr	esi,0
	jc	find_next_window_line
	or	esi,esi
	jz	main_loop
	mov	[window_line],esi
	inc	[window_line_number]
	jmp	moved_window
  ins_key:
	and	byte [fs:18h],not 80h
	test	byte [fs:17h],11b
	jnz	block_paste
  switch_mode:
	xor	[editor_mode],FEMODE_OVERWRITE
	jmp	main_loop
  switch_blocks:
	xor	[editor_mode],FEMODE_VERTICALSEL
	jmp	main_loop
  block_delete:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	cmp	[was_selection],0
	je	get_command
	call	store_status_for_undo
	call	delete_block
	mov	[selection_line],0
	jmp	operation_done
  block_copy:
	cmp	[was_selection],0
	je	get_command
	call	copy_to_clipboard
	jmp	get_command
    copy_to_clipboard:
	cmp	[clipboard],0
	je	allocate_clipboard
	mov	ebx,[clipboard_handle]
	call	release_memory
    allocate_clipboard:
	call	get_block_length
	inc	ecx
	call	get_memory
	mov	[clipboard],eax
	mov	[clipboard_handle],ebx
	or	eax,eax
	jz	not_enough_memory
	mov	edi,[clipboard]
	call	copy_block
	retn
  block_cut:
	cmp	[was_selection],0
	je	get_command
	call	copy_to_clipboard
	jmp	block_delete
  block_paste:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	call	store_status_for_undo
	cmp	[was_selection],0
	je	paste_secureselection_ok
	test	[editor_style],FES_SECURESEL
	jnz	paste_secureselection_ok
	call	delete_block
    paste_secureselection_ok:
	mov	esi,[clipboard]
	or	esi,esi
	jz	operation_done
	call	insert_block
	jc	paste_failed
	test	[editor_style],FES_SECURESEL
	jz	no_selection_after_paste
	mov	eax,[caret_line]
	mov	ecx,[caret_line_number]
	mov	edx,[caret_position]
	xchg	eax,[selection_line]
	xchg	ecx,[selection_line_number]
	xchg	edx,[selection_position]
	mov	[caret_line],eax
	mov	[caret_line_number],ecx
	mov	[caret_position],edx
	jmp	operation_done
    no_selection_after_paste:
	mov	[selection_line],0
	jmp	operation_done
    paste_failed:
	call	undo_changes
	jmp	operation_done
  undo:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	test	[editor_mode],FEMODE_NOUNDO
	jnz	enable_undo
	test	byte [fs:17h],11b
	jnz	redo
	mov	eax,[undo_data]
	test	eax,eax
	jz	get_command
	call	undo_changes
	jmp	operation_done
  redo:
	test	[editor_mode],FEMODE_READONLY
	jnz	get_command
	mov	eax,[redo_data]
	test	eax,eax
	jz	get_command
	call	redo_changes
	jmp	operation_done
  enable_undo:
	and	[editor_mode],not FEMODE_NOUNDO
	jmp	main_loop
  disable_undo:
	call	clear_redo_data
	call	clear_undo_data
	or	[editor_mode],FEMODE_NOUNDO
	jmp	operation_done
  select_all:
	or	eax,-1
	call	find_line
	mov	[caret_line],esi
	mov	[caret_line_number],ecx
	call	check_line_length
	mov	[caret_position],ecx
	mov	eax,1
	call	find_line
	mov	[selection_line],esi
	mov	[selection_line_number],ecx
	mov	[selection_position],0
	jmp	operation_done
  ascii_table:
	call	ascii_table_window
	jc	main_loop
	test	al,al
	jz	main_loop
	cmp	al,1Ah
	je	main_loop
	jmp	character

  moved_caret:
	test	byte [fs:17h],11b
	jnz	operation_done
	mov	[selection_line],0
	jmp	operation_done
  text_modified:
	cmp	[was_selection],0
	jne	operation_done
	mov	[selection_line],0
  operation_done:
	call	update_positions
	call	let_caret_appear
	call	update_window
	jmp	main_loop
  moved_window:
	call	update_positions
	cmp	[was_selection],0
	jne	main_loop
	mov	[selection_line],0
	jmp	main_loop

  new_editor:
	call	create_editor_instance
	jmp	main_loop
  close_editor:
	or	[command_flags],8
	jmp	closing_loop
  close_all:
	and	[command_flags],not 8
    closing_loop:
	mov	eax,[undo_data]
	cmp	eax,[unmodified_state]
	je	do_close
	mov	esi,[file_path]
	call	get_file_title
	mov	ebx,esi
	mov	esi,_saving_question
	mov	eax,2 shl 24
	mov	ax,[message_box_colors]
	mov	[first_button],_yes
	mov	[second_button],_no
	call	message_box
	cmp	eax,1
	jb	main_loop
	ja	do_close
	cmp	[file_path],0
	jne	save_before_closing
	call	get_saving_path
	jc	main_loop
    save_before_closing:
	call	save_file
	jc	main_loop
    do_close:
	call	remove_editor_instance
	jc	shutdown
	test	[command_flags],8
	jnz	main_loop
	call	update_cursor
	call	update_screen
	jmp	closing_loop
  switch_editor:
	test	byte [fs:17h],11b
	jnz	previous_editor
	mov	eax,[next_instance]
	or	eax,eax
	jnz	do_switch
	mov	eax,[previous_instance]
	or	eax,eax
	jz	get_command
    find_first_editor:
	mov	ebx,[eax+SEGMENT_HEADER_LENGTH+previous_instance-editor_data]
	or	ebx,ebx
	jz	do_switch
	mov	eax,ebx
	jmp	find_first_editor
    do_switch:
	call	switch_editor_instance
	jmp	main_loop
    previous_editor:
	mov	eax,[previous_instance]
	or	eax,eax
	jnz	do_switch
	mov	eax,[next_instance]
	or	eax,eax
	jz	get_command
    find_last_editor:
	mov	ebx,[eax+SEGMENT_HEADER_LENGTH+next_instance-editor_data]
	or	ebx,ebx
	jz	do_switch
	mov	eax,ebx
	jmp	find_last_editor
  select_editor:
	mov	eax,[editor_memory]
	mov	edx,[previous_instance]
    prepare_for_editor_counting:
	or	edx,edx
	jz	find_selected_editor
	mov	eax,edx
	mov	edx,[edx+SEGMENT_HEADER_LENGTH+previous_instance-editor_data]
	jmp	prepare_for_editor_counting
    find_selected_editor:
	dec	ecx
	jz	selected_editor_found
	mov	eax,[eax+SEGMENT_HEADER_LENGTH+next_instance-editor_data]
	or	eax,eax
	jz	get_command
	jmp	find_selected_editor
    selected_editor_found:
	cmp	eax,[editor_memory]
	je	get_command
	jmp	do_switch
  show_user_screen:
	call	switch_to_user_screen
	mov	ah,10h
	int	16h
	call	switch_to_ide_screen
	jmp	main_loop

  save_current:
	test	[editor_mode],FEMODE_READONLY
	jnz	save_as
	cmp	[file_path],0
	jne	do_save
  save_as:
	call	get_saving_path
	jc	main_loop
      do_save:
	call	save_file
	jmp	main_loop
  open_file:
	mov	esi,_open
	call	file_open_dialog
	jc	main_loop
	call	load_file
	jmp	main_loop
  goto:
	call	goto_dialog
	jc	main_loop
	or	edx,edx
	jz	goto_position_ok
	dec	edx
	mov	[caret_position],edx
	mov	[selection_position],edx
      goto_position_ok:
	or	ecx,ecx
	jz	goto_line_ok
	mov	eax,ecx
	call	find_line
	mov	[caret_line],esi
	mov	[selection_line],esi
	mov	[caret_line_number],ecx
	mov	[selection_line_number],ecx
      goto_line_ok:
	call	update_positions
	call	let_caret_appear
	call	update_window
	jmp	main_loop
  search:
	call	find_dialog
	jc	main_loop
	call	find_first
	jc	not_found
	call	show_found_text
	jmp	main_loop
      not_found:
	call	update_screen
	mov	edi,buffer+1000h
	push	edi
	call	get_search_text
	mov	edi,buffer
	mov	esi,_not_found_after
	test	[search_flags],FEFIND_BACKWARD
	jz	make_not_found_message
	mov	esi,_not_found_before
      make_not_found_message:
	mov	ebx,esp
	call	sprintf
	pop	eax
	call	release_search_data
	mov	esi,buffer
	mov	ebx,_find
	movzx	eax,[message_box_colors]
	call	message_box
	jmp	main_loop
      show_found_text:
	mov	eax,[caret_position]
	xchg	eax,[selection_position]
	mov	[caret_position],eax
	call	update_positions
	call	let_caret_appear
	call	update_window
	mov	eax,[caret_position]
	xchg	eax,[selection_position]
	mov	[caret_position],eax
	ret
  replace:
	call	replace_dialog
	jc	main_loop
	mov	[replaces_count],0
	push	edi
	call	find_first
	jc	not_found
	call	store_status_for_undo
      replace_loop:
	test	[command_flags],1
	jz	do_replace
	call	show_found_text
	call	let_caret_appear
	call	update_window
	call	update_screen
	mov	ebx,_replace
	mov	esi,_replace_prompt
	mov	eax,2 shl 24
	mov	ax,[message_box_colors]
	mov	[first_button],_yes
	mov	[second_button],_no
	or	[command_flags],80h
	call	message_box
	and	[command_flags],not 80h
	cmp	eax,1
	jb	replacing_finished
	ja	replace_next
      do_replace:
	push	[caret_line_number]
	push	[caret_position]
	call	delete_block
	pop	edx ecx
	cmp	ecx,[caret_line_number]
	jne	simple_replace
	cmp	edx,[caret_position]
	jne	simple_replace
	mov	esi,[esp]
	call	insert_block
	mov	esi,[caret_line]
	mov	ecx,[caret_line_number]
	mov	edx,[caret_position]
	xchg	esi,[selection_line]
	xchg	ecx,[selection_line_number]
	xchg	edx,[selection_position]
	mov	[caret_line],esi
	mov	[caret_line_number],ecx
	mov	[caret_position],edx
	jmp	replace_done
      simple_replace:
	mov	esi,[esp]
	call	insert_block
      replace_done:
	inc	[replaces_count]
      replace_next:
	call	find_next
	jnc	replace_loop
      replacing_finished:
	call	release_search_data
	call	let_caret_appear
	call	update_window
	call	update_screen
	mov	edi,buffer
	mov	esi,_replaces_made
	mov	ebx,replaces_count
	call	sprintf
	mov	esi,buffer
	mov	ebx,_find
	movzx	eax,[message_box_colors]
	call	message_box
	jmp	main_loop
  search_next:
	cmp	[search_data],0
	je	main_loop
	call	find_next
	jc	not_found
	call	show_found_text
	jmp	main_loop
  build_symbols:
	and	[command_flags],not 2
	or	[command_flags],4
	jmp	do_compile
  compile:
	and	[command_flags],not (2 or 4)
	jmp	do_compile
  compile_and_run:
	and	[command_flags],not 4
	or	[command_flags],2
      do_compile:
	push	[editor_memory]
	mov	eax,[main_project_file]
	or	eax,eax
	jz	got_main_file
	call	switch_editor_instance
      got_main_file:
	cmp	[file_path],0
	jne	main_file_path_ok
	call	update_screen
	call	get_saving_path
	jc	main_loop
	call	update_screen
      main_file_path_ok:
	mov	eax,[editor_memory]
	push	eax
	mov	edx,[previous_instance]
	test	edx,edx
	jz	save_all_files
	mov	eax,edx
      find_first_to_save:
	mov	edx,[eax+SEGMENT_HEADER_LENGTH+previous_instance-editor_data]
	or	edx,edx
	jz	save_all_files
	mov	eax,edx
	jmp	find_first_to_save
      save_all_files:
	call	switch_editor_instance
	cmp	[file_path],0
	je	save_next
	mov	eax,[undo_data]
	cmp	eax,[unmodified_state]
	je	save_next
	call	save_file
	jc	main_loop
      save_next:
	mov	eax,[next_instance]
	or	eax,eax
	jnz	save_all_files
	pop	eax
	call	switch_editor_instance
	mov	edi,buffer+3000h
	mov	byte [edi],0
	call	get_current_directory
	mov	esi,[file_path]
	mov	edi,buffer
	mov	ebx,edi
      copy_directory_path:
	lodsb
	or	al,al
	jz	directory_path_ok
	stosb
	cmp	al,'\'
	jne	copy_directory_path
	mov	ebx,edi
	jmp	copy_directory_path
      directory_path_ok:
	mov	byte [ebx],0
	mov	esi,buffer
	call	go_to_directory
	mov	eax,[file_path]
	mov	[input_file],eax
	mov	[symbols_file],0
	test	[command_flags],4
	jz	symbols_file_name_ok
	mov	edi,buffer+2000h
	mov	[symbols_file],edi
	mov	esi,eax
	xor	ebx,ebx
      copy_file_name:
	lodsb
	stosb
	test	al,al
	jz	file_name_copied
	cmp	al,'.'
	jne	copy_file_name
	mov	ebx,edi
	jmp	copy_file_name
      file_name_copied:
	test	ebx,ebx
	jz	attach_fas_extension
	mov	edi,ebx
      attach_fas_extension:
	dec	edi
	mov	eax,'.fas'
	stosd
	xor	al,al
	stosb
      symbols_file_name_ok:
	pop	eax
	call	switch_editor_instance
	mov	cx,1000h
	mov	ah,1
	int	10h
	mov	esi,_compile
	mov	cx,0316h
	mov	ah,[window_colors]
	call	draw_centered_window
	add	edi,2
	mov	[progress_offset],edi
	mov	eax,[memory_limit]
	test	eax,eax
	jnz	allocate_memory
	mov	ax,500h
	mov	edi,buffer
	int	31h
	mov	eax,[edi]
      allocate_memory:
	mov	ecx,eax
	mov	edx,eax
	shr	edx,2
	sub	eax,edx
	mov	[memory_end],eax
	mov	[additional_memory_end],edx
	call	get_memory
	or	eax,eax
	jnz	memory_allocated
	mov	eax,[additional_memory_end]
	shl	eax,1
	cmp	eax,4000h
	jb	not_enough_memory
	jmp	allocate_memory
      get_current_directory:
	mov	ah,19h
	int	21h
	mov	bl,al
	mov	dl,al
	inc	dl
	xor	esi,esi
	mov	ax,7147h
	call	dos_int
	jnc	got_current_directory
	cmp	ax,7100h
	je	get_current_directory_short
      invalid_current_directory:
	stc
	ret
      get_current_directory_short:
	mov	ah,47h
	call	dos_int
	jc	invalid_current_directory
      got_current_directory:
	cmp	byte [buffer],0
	je	drive_prefix
	cmp	byte [buffer+1],':'
	je	copy_current_directory
	cmp	word [buffer],'\\'
	je	copy_current_directory
      drive_prefix:
	mov	al,bl
	add	al,'A'
	mov	ah,':'
	stosw
	mov	al,'\'
	stosb
      copy_current_directory:
	mov	esi,buffer
	call	copy_asciiz
	clc
	ret
      go_to_directory:
	cmp	esi,buffer
	je	directory_path_ready
	mov	edi,buffer
	call	copy_asciiz
	mov	esi,buffer
      directory_path_ready:
	mov	ah,0Eh
	mov	dl,[buffer]
	sub	dl,'A'
	jc	current_directory_ok
	cmp	dl,'Z'-'A'
	jbe	change_current_drive
	sub	dl,'a'-'A'
      change_current_drive:
	int	21h
	xor	dx,dx
	mov	ax,713Bh
	call	dos_int
	cmp	ax,7100h
	jne	current_directory_ok
	mov	ah,3Bh
	call	dos_int
      current_directory_ok:
	ret
      memory_allocated:
	mov	[allocated_memory],ebx
	mov	[memory_start],eax
	add	eax,[memory_end]
	mov	[memory_end],eax
	mov	[additional_memory],eax
	add	[additional_memory_end],eax
	xor	eax,eax
	mov	[initial_definitions],eax
	mov	[output_file],eax
	mov	[display_length],eax
	mov	ax,204h
	mov	bl,9
	int	31h
	mov	dword [keyboard_handler],edx
	mov	word [keyboard_handler+4],cx
	mov	ax,205h
	mov	bl,9
	mov	cx,cs
	mov	edx,aborting_handler
	int	31h
	mov	eax,[fs:6Ch]
	mov	[start_time],eax
	call	preprocessor
	call	draw_progress_segment
	call	parser
	call	draw_progress_segment
	call	assembler
	call	draw_progress_segment
	call	formatter
	call	draw_progress_segment
	mov	ax,205h
	mov	bl,9
	mov	edx,dword [keyboard_handler]
	mov	cx,word [keyboard_handler+4]
	int	31h
	test	[command_flags],2
	jnz	execute
	mov	esi,buffer+3000h
	call	go_to_directory
	call	show_display_buffer
	call	update_screen
	mov	edi,buffer
	movzx	eax,[current_pass]
	inc	eax
	call	number_as_text
	mov	eax,' pas'
	stosd
	mov	eax,'ses,'
	stosd
	mov	al,20h
	stosb
	mov	eax,[fs:6Ch]
	sub	eax,[start_time]
	mov	ebx,100
	mul	ebx
	mov	ebx,182
	div	ebx
	or	eax,eax
	jz	show_bytes_count
	xor	edx,edx
	mov	ebx,10
	div	ebx
	push	edx
	call	number_as_text
	mov	al,'.'
	stosb
	pop	eax
	call	number_as_text
	mov	eax,' sec'
	stosd
	mov	eax,'onds'
	stosd
	mov	ax,', '
	stosw
      show_bytes_count:
	mov	eax,[written_size]
	call	number_as_text
	mov	eax,' byt'
	stosd
	mov	eax,'es.'
	stosd
	mov	ebx,[allocated_memory]
	call	release_memory
	mov	esi,buffer
	mov	ebx,_compile
	movzx	eax,[message_box_colors]
	mov	[first_button],_ok
	mov	[second_button],_get_display
	cmp	[display_length],0
	je	show_compilation_summary
	or	eax,2 shl 24
      show_compilation_summary:
	call	message_box
	cmp	eax,2
	jb	main_loop
	cmp	[clipboard],0
	je	get_display_to_clipboard
	mov	ebx,[clipboard_handle]
	call	release_memory
      get_display_to_clipboard:
	mov	ecx,[display_length]
	inc	ecx
	call	get_memory
	mov	[clipboard_handle],ebx
	mov	[clipboard],eax
	or	eax,eax
	jz	not_enough_memory
	xor	esi,esi
	mov	edi,eax
	mov	ecx,[display_length]
	push	ds
	mov	ds,[low_memory_selector]
	rep	movsb
	pop	ds
	xor	al,al
	stosb
	jmp	main_loop
    execute:
	mov	edx,[output_file]
	call	adapt_path
	mov	ebx,[allocated_memory]
	call	release_memory
	cmp	[output_format],3
	ja	cannot_execute
	call	release_low_memory
	call	switch_to_user_screen
	call	close_video
	mov	edi,buffer+200h
	lea	edx,[edi-buffer]
	mov	ax,0D00h
	stosw
	lea	esi,[edi-buffer]
	xor	al,al
	stosb
	mov	al,20h
	mov	ecx,11
	rep	stosb
	xor	al,al
	mov	ecx,25
	rep	stosb
	lea	ebx,[edi-buffer]
	xor	eax,eax
	stosw
	mov	ax,buffer_segment
	shl	eax,16
	mov	ax,dx
	stosd
	mov	ax,si
	stosd
	stosd
	mov	ax,4B00h
	xor	dx,dx
	call	dos_int
	mov	esi,buffer+3000h
	call	go_to_directory
	call	init_video
	jc	startup_failed
	call	switch_to_ide_screen
	call	get_low_memory
	jmp	main_loop
      cannot_execute:
	mov	esi,buffer+3000h
	call	go_to_directory
	mov	esi,_not_executable
	mov	ebx,_error
	movzx	eax,[error_box_colors]
	call	message_box
	jmp	main_loop
    draw_progress_segment:
	mov	eax,[progress_offset]
	mov	ecx,4
      draw_progress_filler:
	mov	byte [gs:eax],254
	add	eax,2
	loop	draw_progress_filler
	mov	[progress_offset],eax
	ret
    aborting_handler:
	push	eax
	in	al,60h
	cmp	al,1
	jne	no_abort
	mov	dword [esp+4],abort_compiling
	mov	word [esp+4+4],cs
      no_abort:
	pop	eax
	jmp	pword [cs:keyboard_handler]
      abort_compiling:
	cli
	mov	ax,[cs:main_selector]
	mov	esp,stack_top
	mov	ss,ax
	mov	ds,ax
	mov	es,ax
	mov	fs,[bios_selector]
	mov	gs,[video_selector]
	mov	ax,205h
	mov	bl,9
	mov	edx,dword [keyboard_handler]
	mov	cx,word [keyboard_handler+4]
	int	31h
	sti
      discard_keyboard_buffer:
	mov	ah,11h
	int	16h
	jz	keyboard_buffer_ok
	mov	ah,10h
	int	16h
	jmp	discard_keyboard_buffer
      keyboard_buffer_ok:
	mov	ebx,[allocated_memory]
	call	release_memory
	mov	esi,buffer+3000h
	call	go_to_directory
	jmp	main_loop
  assign_to_compiler:
	mov	eax,[editor_memory]
	xchg	eax,[main_project_file]
	cmp	eax,[editor_memory]
	jne	main_loop
	mov	[main_project_file],0
	jmp	main_loop
  calculator:
	call	calculator_window
	jmp	main_loop
  options:
	push	[editor_style]
	call	options_dialog
	pop	eax
	jnc	main_loop
	mov	[editor_style],eax
	jmp	main_loop

  startup_failed:
	mov	esi,_startup_failed
      error_message_loop:
	lodsb
	or	al,al
	jz	error_message_ok
	mov	dl,al
	mov	ah,2
	int	21h
	jmp	error_message_loop
      error_message_ok:
	mov	ax,4C0Fh
	int	21h

  init_video:
	call	check_video_mode
	mov	bx,gs
	movzx	edx,byte [fs:4Ah]
	mov	[screen_width],edx
	shl	edx,1
	mov	[video_pitch],edx
	movzx	eax,byte [fs:84h]
	inc	eax
	mov	[screen_height],eax
	imul	edx,eax
	push	edx
	dec	edx
	shld	ecx,edx,16
	mov	ax,8
	int	31h
	jc	video_init_failed
	pop	ecx
	call	get_memory
	jc	video_init_failed
	mov	[video_storage],eax
	mov	[video_storage_handle],ebx
	clc
	ret
    video_init_failed:
	stc
	ret
    check_video_mode:
	test	byte [fs:65h],110b
	jnz	set_video_mode
	cmp	byte [fs:4Ah],80
	jb	set_video_mode
	ret
    set_video_mode:
	mov	ax,3
	int	10h
	ret
  close_video:
	mov	ebx,[video_storage_handle]
	call	release_memory
	ret
  switch_to_ide_screen:
	call	check_video_mode
	xor	esi,esi
	mov	edi,[video_storage]
	mov	ecx,[video_pitch]
	imul	ecx,[screen_height]
	rep	movs byte [es:edi],[gs:esi]
	mov	ah,3
	xor	bh,bh
	int	10h
	mov	[stored_cursor],cx
	mov	[stored_cursor_position],dx
	mov	ah,0Fh
	int	10h
	mov	[stored_page],bh
	mov	ax,0500h
	int	10h
	mov	al,[fs:65h]
	mov	[stored_mode],al
	mov	ax,1003h
	xor	bx,bx
	int	10h
	mov	eax,[screen_width]
	mov	[window_width],eax
	mov	eax,[screen_height]
	sub	eax,2
	mov	[window_height],eax
	call	update_window
	ret
  switch_to_user_screen:
	push	es gs
	pop	es
	mov	esi,[video_storage]
	xor	edi,edi
	mov	ecx,[video_pitch]
	imul	ecx,[screen_height]
	rep	movs byte [es:edi],[ds:esi]
	mov	ah,1
	mov	cx,[stored_cursor]
	int	10h
	mov	ah,2
	xor	bh,bh
	mov	dx,[stored_cursor_position]
	int	10h
	mov	ah,5
	mov	al,[stored_page]
	int	10h
	mov	ax,1003h
	xor	bh,bh
	mov	bl,[stored_mode]
	shr	bl,5
	and	bl,1
	int	10h
	pop	es
	ret

  create_editor_instance:
	call	flush_editor_data
	mov	esi,[editor_memory]
    find_last_instance:
	mov	eax,[esi+SEGMENT_HEADER_LENGTH+next_instance-editor_data]
	or	eax,eax
	jz	attach_new_instance
	mov	esi,eax
	jmp	find_last_instance
    attach_new_instance:
	push	esi
	call	init_editor_memory
	pop	esi
	jc	not_enough_memory
	mov	eax,[editor_memory]
	xchg	eax,[esi+SEGMENT_HEADER_LENGTH+next_instance-editor_data]
	mov	[next_instance],eax
	mov	[previous_instance],esi
	xor	eax,eax
	mov	[file_path],eax
     flush_editor_data:
	mov	edi,[editor_memory]
	test	edi,edi
	jz	flush_ok
	add	edi,SEGMENT_HEADER_LENGTH
	mov	esi,editor_data
	mov	ecx,editor_data_size
	rep	movsb
      flush_ok:
	ret
  switch_editor_instance:
	call	flush_editor_data
	cmp	eax,[editor_memory]
	je	editor_switch_ok
	mov	[editor_memory],eax
	lea	esi,[eax+SEGMENT_HEADER_LENGTH]
	mov	edi,editor_data
	mov	ecx,editor_data_size
	rep	movsb
    editor_switch_ok:
	call	update_positions
	ret
  remove_editor_instance:
	mov	eax,[editor_memory]
	xor	eax,[main_project_file]
	jnz	main_project_file_ok
	mov	[main_project_file],eax
    main_project_file_ok:
	mov	esi,[previous_instance]
	mov	edi,[next_instance]
	mov	eax,edi
	or	edi,edi
	jz	next_instance_links_ok
	mov	[edi+SEGMENT_HEADER_LENGTH+previous_instance-editor_data],esi
    next_instance_links_ok:
	or	esi,esi
	jz	previous_instance_links_ok
	mov	[esi+SEGMENT_HEADER_LENGTH+next_instance-editor_data],edi
	mov	eax,esi
    previous_instance_links_ok:
	push	eax
	call	release_editor_memory
	mov	eax,[file_path]
	or	eax,eax
	jz	file_path_released
	mov	ebx,[file_path_handle]
	call	release_memory
    file_path_released:
	pop	eax
	or	eax,eax
	jz	no_instance_left
	call	switch_editor_instance
	clc
	ret
    no_instance_left:
	stc
	ret

  load_file:
	push	edx [editor_memory]
	call	get_full_pathname
	push	esi
	call	flush_editor_data
	mov	esi,[esp]
	mov	edx,[editor_memory]
      prepare_to_scan_editors:
	mov	eax,[edx+SEGMENT_HEADER_LENGTH+previous_instance-editor_data]
	or	eax,eax
	jz	scan_editors
	mov	edx,eax
	jmp	prepare_to_scan_editors
      scan_editors:
	mov	edi,[edx+SEGMENT_HEADER_LENGTH+file_path-editor_data]
	or	edi,edi
	jz	scan_next_editor
	xor	ecx,ecx
	mov	ebx,lower_case_table
      compare_pathnames:
	mov	al,[esi+ecx]
	xlatb
	mov	ah,al
	mov	al,[edi+ecx]
	xlatb
	cmp	al,ah
	jne	scan_next_editor
	or	al,ah
	jz	file_found
	inc	ecx
	jmp	compare_pathnames
      scan_next_editor:
	mov	edx,[edx+SEGMENT_HEADER_LENGTH+next_instance-editor_data]
	or	edx,edx
	jnz	scan_editors
	mov	eax,[undo_data]
	sub	eax,[unmodified_state]
	or	eax,[file_path]
	jz	open_in_current_instance
	call	create_editor_instance
      open_in_current_instance:
	pop	esi
	call	use_pathname
	mov	edx,[file_path]
	call	open
	jc	load_failed
	xor	edx,edx
	mov	al,2
	call	lseek
	push	eax ebx
	lea	ecx,[eax+1]
	call	get_memory
	or	eax,eax
	jz	not_enough_memory
	mov	esi,eax
	mov	edi,ecx
	pop	ebx
	xor	edx,edx
	xor	al,al
	call	lseek
	pop	ecx
	mov	edx,esi
	mov	byte [edx+ecx],0
	call	read
	jc	load_failed
	call	close
	push	edi
	call	set_text
	pop	ebx
	call	release_memory
	add	esp,8
	ret
      file_found:
	mov	eax,edx
	call	switch_editor_instance
	pop	esi
	add	esp,8
	ret
    load_failed:
	mov	eax,[previous_instance]
	or	eax,[next_instance]
	jnz	cancel_instance
      cancel_path_only:
	xor	ebx,ebx
	xchg	ebx,[file_path]
	call	release_memory
	jmp	editor_cancelled
      cancel_instance:
	mov	eax,[editor_memory]
	cmp	eax,[esp]
	je	cancel_path_only
	call	remove_editor_instance
      editor_cancelled:
	pop	eax
	call	switch_editor_instance
	call	update_screen
	mov	edi,buffer
	mov	esi,_loading_error
	mov	ebx,esp
	call	sprintf
	pop	eax
	mov	esi,buffer
	mov	ebx,_error
	movzx	eax,[error_box_colors]
	call	message_box
	ret
  get_full_pathname:
	call	adapt_path
	sub	edi,buffer
	mov	ax,7160h
	xor	cx,cx
	xor	si,si
	stc
	call	dos_int
	jnc	got_full_pathname
	mov	ah,60h
	call	dos_int
	jc	full_pathname_exit
      got_full_pathname:
	lea	esi,[buffer + edi]
	cmp	word [esi],'\\'
	jne	full_pathname_ok
	cmp	dword [esi+3],'.\A.'
	jne	full_pathname_ok
	mov	al,[esi+2]
	mov	ah,':'
	add	esi,5
	mov	[esi],ax
      full_pathname_ok:
	clc
      full_pathname_exit:
	ret
  use_pathname:
	mov	edi,[file_path]
	or	edi,edi
	jnz	copy_pathname
	mov	ecx,1000h
	push	esi
	call	get_memory
	pop	esi
	or	eax,eax
	jz	not_enough_memory
	mov	edi,eax
	mov	[file_path],edi
	mov	[file_path_handle],ebx
      copy_pathname:
	lodsb
	stosb
	or	al,al
	jnz	copy_pathname
	ret
  save_file:
	mov	edx,[file_path]
	call	create
	jc	file_creation_error
	mov	[file_handle],ebx
	mov	esi,[first_line]
	mov	edi,[line_buffer]
    copy_text:
	mov	ecx,[esi+8]
	lea	eax,[edi+ecx]
	mov	edx,[line_buffer_size]
	shr	edx,1
	sub	eax,edx
	cmp	eax,[line_buffer]
	ja	flush_to_file
	mov	ebp,edi
	xor	edx,edx
	push	ecx
	call	copy_from_line
	pop	ecx
	test	[editor_style],FES_OPTIMALFILL
	jz	line_copied
	cmp	ecx,8
	jb	line_copied
	push	esi edi ecx
	mov	esi,ebp
	mov	edi,[line_buffer]
	mov	eax,[line_buffer_size]
	shr	eax,1
	add	edi,eax
	push	edi
	mov	ecx,[esp+4]
	xor	al,al
	rep	stosb
	mov	ecx,[esp+4]
	mov	edi,[esp]
	call	syntax_proc
	pop	ebx ecx edi
	mov	esi,ebp
	mov	edi,ebp
	sub	ebx,esi
	xor	edx,edx
    optimal_fill:
	lodsb
	cmp	al,20h
	jne	store_character
	cmp	byte [esi-1+ebx],0
	jne	store_character
	mov	eax,esi
	sub	eax,ebp
	test	eax,111b
	jz	store_tab
	inc	edx
	mov	al,20h
	stosb
	loop	optimal_fill
	jmp	optimal_fill_done
    store_tab:
	mov	al,20h
	or	edx,edx
	jz	store_character
	sub	edi,edx
	mov	al,9
    store_character:
	stosb
	xor	edx,edx
	loop	optimal_fill
    optimal_fill_done:
	pop	esi
	jmp	line_copied
    line_copied:
	or	esi,esi
	jz	flush_to_file
	mov	ax,0A0Dh
	stosw
	jmp	copy_text
    flush_to_file:
	push	esi
	mov	edx,[line_buffer]
	mov	ecx,edi
	sub	ecx,edx
	mov	ebx,[file_handle]
	call	write
	jc	file_writing_error
	pop	esi
	mov	edi,[line_buffer]
	or	esi,esi
	jnz	copy_text
	mov	ebx,[file_handle]
	call	close
	mov	eax,[undo_data]
	mov	[unmodified_state],eax
	clc
	ret
    file_writing_error:
	add	esp,4
    file_creation_error:
	call	update_screen
	mov	esi,_saving_error
	mov	ebx,_error
	movzx	eax,[error_box_colors]
	call	message_box
	stc
	ret
  get_saving_path:
	mov	esi,_save_as
	call	file_open_dialog
	jc	saving_aborted
	push	edx
	cmp	byte [edx+ecx-1],'\'
	je	save_in_new_directory
	call	open
	pop	edx
	jc	saving_allowed
	push	edx
	call	close
	call	update_screen
	mov	edi,buffer
	mov	esi,_overwrite_question
	mov	ebx,esp
	call	sprintf
	mov	esi,buffer
	mov	ebx,_save_as
	mov	eax,2 shl 24
	mov	ax,[message_box_colors]
	mov	[first_button],_yes
	mov	[second_button],_no
	call	message_box
	pop	edx
	cmp	eax,1
	jb	saving_aborted
	je	saving_allowed
	call	update_screen
	jmp	get_saving_path
     save_in_new_directory:
	mov	byte [edx+ecx-1],0
	call	update_screen
	mov	edi,buffer
	mov	esi,_directory_question
	mov	ebx,esp
	call	sprintf
	mov	esi,buffer
	mov	ebx,_save_as
	mov	eax,2 shl 24
	mov	ax,[message_box_colors]
	mov	[first_button],_yes
	mov	[second_button],_no
	call	message_box
	pop	esi
	cmp	eax,1
	jb	saving_aborted
	jne	saving_directory_ok
	mov	edi,buffer
	call	copy_asciiz
	mov	ax,7139h
	xor	edx,edx
	call	dos_int
	jnc	new_directory_created
	cmp	ax,7100h
	jne	error_creating_directory
	mov	ah,39h
	call	dos_int
	jc	error_creating_directory
     new_directory_created:
	mov	ax,713Bh
	call	dos_int
	jnc	saving_directory_ok
	cmp	ax,7100h
	jne	error_creating_directory
	mov	ah,3Bh
	call	dos_int
	jc	error_creating_directory
     saving_directory_ok:
	call	update_screen
	jmp	get_saving_path
     error_creating_directory:
	call	update_screen
	mov	esi,_directory_error
	mov	ebx,_error
	movzx	eax,[error_box_colors]
	call	message_box
	jmp	saving_directory_ok
     saving_allowed:
	call	get_full_pathname
	jc	invalid_saving_path
	call	use_pathname
	clc
	ret
     invalid_saving_path:
	call	update_screen
	mov	esi,_invalid_path
	mov	ebx,_error
	movzx	eax,[error_box_colors]
	call	message_box
     saving_aborted:
	stc
	ret

  load_configuration:
	call	load_ini_file
	xor	eax,eax
	mov	[memory_limit],eax
	mov	al,100
	mov	[passes_limit],ax
	mov	ebx,_section_compiler
	mov	esi,_key_compiler_memory
	call	get_ini_int
	jc	memory_setting_ok
	cmp	eax,1 shl (32-10)
	jae	memory_setting_ok
	shl	eax,10
	mov	[memory_limit],eax
      memory_setting_ok:
	mov	esi,_key_compiler_passes
	call	get_ini_int
	jc	passes_setting_ok
	test	eax,eax
	jz	passes_setting_ok
	cmp	eax,10000h
	ja	passes_setting_ok
	mov	[passes_limit],ax
      passes_setting_ok:
	mov	ebx,_section_options
	mov	esi,_key_options_securesel
	call	get_ini_int
	jc	securesel_init_ok
	and	[editor_style],not FES_SECURESEL
	test	eax,eax
	jz	securesel_init_ok
	or	[editor_style],FES_SECURESEL
     securesel_init_ok:
	mov	esi,_key_options_autobrackets
	call	get_ini_int
	jc	autobrackets_init_ok
	and	[editor_style],not FES_AUTOBRACKETS
	test	eax,eax
	jz	autobrackets_init_ok
	or	[editor_style],FES_AUTOBRACKETS
     autobrackets_init_ok:
	mov	esi,_key_options_autoindent
	call	get_ini_int
	jc	autoindent_init_ok
	and	[editor_style],not FES_AUTOINDENT
	test	eax,eax
	jz	autoindent_init_ok
	or	[editor_style],FES_AUTOINDENT
     autoindent_init_ok:
	mov	esi,_key_options_smarttabs
	call	get_ini_int
	jc	smarttabs_init_ok
	and	[editor_style],not FES_SMARTTABS
	test	eax,eax
	jz	smarttabs_init_ok
	or	[editor_style],FES_SMARTTABS
     smarttabs_init_ok:
	mov	esi,_key_options_optimalfill
	call	get_ini_int
	jc	optimalfill_init_ok
	and	[editor_style],not FES_OPTIMALFILL
	test	eax,eax
	jz	optimalfill_init_ok
	or	[editor_style],FES_OPTIMALFILL
     optimalfill_init_ok:
	mov	ebx,_section_colors
	mov	esi,_key_color_text
	call	get_ini_int
	jc	color_text_init_ok
	and	al,0Fh
	and	[text_colors],0F0h
	or	[text_colors],al
     color_text_init_ok:
	mov	esi,_key_color_background
	call	get_ini_int
	jc	color_background_init_ok
	and	al,0Fh
	shl	al,4
	and	[text_colors],0Fh
	or	[text_colors],al
     color_background_init_ok:
	mov	esi,_key_color_seltext
	call	get_ini_int
	jc	color_seltext_init_ok
	and	al,0Fh
	and	[selection_colors],0F0h
	or	[selection_colors],al
     color_seltext_init_ok:
	mov	esi,_key_color_selbackground
	call	get_ini_int
	jc	color_selbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	[selection_colors],0Fh
	or	[selection_colors],al
     color_selbackground_init_ok:
	mov	esi,_key_color_symbols
	call	get_ini_int
	jc	color_symbols_init_ok
	mov	[symbol_color],al
     color_symbols_init_ok:
	mov	esi,_key_color_numbers
	call	get_ini_int
	jc	color_numbers_init_ok
	mov	[number_color],al
     color_numbers_init_ok:
	mov	esi,_key_color_strings
	call	get_ini_int
	jc	color_strings_init_ok
	mov	[string_color],al
     color_strings_init_ok:
	mov	esi,_key_color_comments
	call	get_ini_int
	jc	color_comments_init_ok
	mov	[comment_color],al
     color_comments_init_ok:
	mov	esi,_key_color_statustext
	call	get_ini_int
	jc	color_statustext_init_ok
	and	al,0Fh
	and	[status_colors],0F0h
	or	[status_colors],al
     color_statustext_init_ok:
	mov	esi,_key_color_statusbackground
	call	get_ini_int
	jc	color_statusbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	[status_colors],0Fh
	or	[status_colors],al
     color_statusbackground_init_ok:
	mov	esi,_key_color_wintext
	call	get_ini_int
	jc	color_wintext_init_ok
	and	al,0Fh
	and	[window_colors],0F0h
	or	[window_colors],al
     color_wintext_init_ok:
	mov	esi,_key_color_winbackground
	call	get_ini_int
	jc	color_winbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	[window_colors],0Fh
	or	[window_colors],al
     color_winbackground_init_ok:
	mov	esi,_key_color_msgtext
	call	get_ini_int
	jc	color_msgtext_init_ok
	and	al,0Fh
	and	byte [message_box_colors+1],0F0h
	or	byte [message_box_colors+1],al
     color_msgtext_init_ok:
	mov	esi,_key_color_msgbackground
	call	get_ini_int
	jc	color_msgbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	byte [message_box_colors+1],0Fh
	or	byte [message_box_colors+1],al
     color_msgbackground_init_ok:
	mov	esi,_key_color_msgseltext
	call	get_ini_int
	jc	color_msgseltext_init_ok
	and	al,0Fh
	and	byte [message_box_colors],0F0h
	or	byte [message_box_colors],al
     color_msgseltext_init_ok:
	mov	esi,_key_color_msgselbackground
	call	get_ini_int
	jc	color_msgselbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	byte [message_box_colors],0Fh
	or	byte [message_box_colors],al
     color_msgselbackground_init_ok:
	mov	esi,_key_color_errtext
	call	get_ini_int
	jc	color_errtext_init_ok
	and	al,0Fh
	and	byte [error_box_colors+1],0F0h
	or	byte [error_box_colors+1],al
     color_errtext_init_ok:
	mov	esi,_key_color_errbackground
	call	get_ini_int
	jc	color_errbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	byte [error_box_colors+1],0Fh
	or	byte [error_box_colors+1],al
     color_errbackground_init_ok:
	mov	esi,_key_color_errseltext
	call	get_ini_int
	jc	color_errseltext_init_ok
	and	al,0Fh
	and	byte [error_box_colors],0F0h
	or	byte [error_box_colors],al
     color_errseltext_init_ok:
	mov	esi,_key_color_errselbackground
	call	get_ini_int
	jc	color_errselbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	byte [error_box_colors],0Fh
	or	byte [error_box_colors],al
     color_errselbackground_init_ok:
	mov	esi,_key_color_boxtext
	call	get_ini_int
	jc	color_boxtext_init_ok
	and	al,0Fh
	and	[box_colors],0F0h
	or	[box_colors],al
     color_boxtext_init_ok:
	mov	esi,_key_color_boxbackground
	call	get_ini_int
	jc	color_boxbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	[box_colors],0Fh
	or	[box_colors],al
     color_boxbackground_init_ok:
	mov	esi,_key_color_boxseltext
	call	get_ini_int
	jc	color_boxseltext_init_ok
	and	al,0Fh
	and	byte [box_selection_colors],0F0h
	or	byte [box_selection_colors],al
     color_boxseltext_init_ok:
	mov	esi,_key_color_boxselbackground
	call	get_ini_int
	jc	color_boxselbackground_init_ok
	and	al,0Fh
	shl	al,4
	and	byte [box_selection_colors],0Fh
	or	byte [box_selection_colors],al
     color_boxselbackground_init_ok:
	ret
  load_ini_file:
	cmp	[ini_data],0
	je	open_ini_file
	mov	ebx,[ini_data_handle]
	call	release_memory
      open_ini_file:
	mov	edx,ini_path
	call	open
	jc	no_ini_file
	xor	edx,edx
	mov	al,2
	call	lseek
	push	eax
	xor	edx,edx
	xor	al,al
	call	lseek
	mov	ecx,[esp]
	add	ecx,800h
	push	ebx
	call	get_memory
	mov	[ini_data],eax
	mov	[ini_data_handle],ebx
	pop	ebx ecx
	test	eax,eax
	jz	ini_loaded
	mov	edx,eax
	mov	byte [edx+ecx],1Ah
	mov	[ini_data_length],ecx
	call	read
	call	close
	ret
      no_ini_file:
	mov	ecx,800h
	call	get_memory
	mov	[ini_data],eax
	test	eax,eax
	jz	ini_loaded
	mov	byte [eax],1Ah
	mov	[ini_data_length],0
      ini_loaded:
	ret
  get_ini_value:
	mov	edi,esi
	mov	esi,[ini_data]
	test	esi,esi
	jz	ini_value_not_found
	call	find_ini_block
	jc	ini_value_not_found
	call	find_ini_value
	ret
     ini_value_not_found:
	stc
	ret
     find_ini_block:
	lodsb
	cmp	al,20h
	je	find_ini_block
	cmp	al,9
	je	find_ini_block
	cmp	al,'['
	jne	look_for_ini_block_in_next_line
     find_block_name:
	lodsb
	cmp	al,20h
	je	find_block_name
	cmp	al,9
	je	find_block_name
	dec	esi
	mov	edx,ebx
     compare_block_name_char:
	lodsb
	mov	ah,[edx]
	inc	edx
	cmp	al,']'
	je	end_of_block_name
	cmp	al,20h
	je	end_of_block_name
	cmp	al,9
	je	end_of_block_name
	cmp	al,1Ah
	je	end_of_block_name
	cmp	al,0Dh
	je	end_of_block_name
	cmp	al,0Ah
	je	end_of_block_name
	or	ah,ah
	jz	look_for_ini_block_in_next_line
	sub	ah,al
	jz	compare_block_name_char
	jns	block_name_char_case_insensitive
	neg	ah
	sub	al,20h
     block_name_char_case_insensitive:
	cmp	ah,20h
	jne	look_for_ini_block_in_next_line
	cmp	al,41h
	jb	look_for_ini_block_in_next_line
	cmp	al,5Ah
	jna	compare_block_name_char
     look_for_ini_block_in_next_line:
	dec	esi
	call	find_next_ini_line
	cmp	byte [esi],1Ah
	jne	find_ini_block
	stc
	ret
     end_of_block_name:
	test	ah,ah
	jnz	look_for_ini_block_in_next_line
	cmp	al,']'
	je	end_of_block_name_ok
	cmp	al,20h
	je	find_block_name_closing_bracket
	cmp	al,9
	jne	look_for_ini_block_in_next_line
     find_block_name_closing_bracket:
	lodsb
	jmp	end_of_block_name
     end_of_block_name_ok:
	call	find_next_ini_line
	clc
	ret
     find_next_ini_line:
	lodsb
	cmp	al,0Dh
	je	line_ending
	cmp	al,0Ah
	je	line_ending
	cmp	al,1Ah
	jne	find_next_ini_line
	dec	esi
	ret
     line_ending:
	lodsb
	cmp	al,0Dh
	je	line_ending
	cmp	al,0Ah
	je	line_ending
	dec	esi
	ret
     find_ini_value:
	lodsb
	cmp	al,20h
	je	find_ini_value
	cmp	al,9
	je	find_ini_value
	cmp	al,0Dh
	je	next_ini_value
	cmp	al,0Ah
	je	next_ini_value
	dec	esi
	cmp	al,1Ah
	je	no_ini_value_found
	cmp	al,'['
	je	no_ini_value_found
	mov	edx,edi
     compare_value_name_char:
	lodsb
	mov	ah,[edx]
	inc	edx
	cmp	al,'='
	je	end_of_value_name
	cmp	al,20h
	je	end_of_value_name
	cmp	al,9
	je	end_of_value_name
	cmp	al,1Ah
	je	end_of_value_name
	cmp	al,0Dh
	je	end_of_value_name
	cmp	al,0Ah
	je	end_of_value_name
	or	ah,ah
	jz	next_ini_value
	sub	ah,al
	jz	compare_value_name_char
	jns	value_name_char_case_insensitive
	neg	ah
	sub	al,20h
     value_name_char_case_insensitive:
	cmp	ah,20h
	jne	next_ini_value
	cmp	al,41h
	jb	next_ini_value
	cmp	al,5Ah
	jna	compare_value_name_char
     next_ini_value:
	dec	esi
	call	find_next_ini_line
	cmp	byte [esi],1Ah
	jne	find_ini_value
     no_ini_value_found:
	stc
	ret
     end_of_value_name:
	test	ah,ah
	jnz	next_ini_value
	cmp	al,'='
	je	ini_value_found
	cmp	al,20h
	je	find_ini_value_start
	cmp	al,9
	jne	next_ini_value
     find_ini_value_start:
	lodsb
	jmp	end_of_value_name
     ini_value_found:
	xor	ecx,ecx
     find_value_length:
	cmp	byte [esi+ecx],0Dh
	je	value_length_found
	cmp	byte [esi+ecx],0Ah
	je	value_length_found
	cmp	byte [esi+ecx],1Ah
	je	value_length_found
	inc	ecx
	jmp	find_value_length
     value_length_found:
	clc
	ret
  get_ini_int:
	call	get_ini_value
	jc	no_ini_int
	push	ebx
	call	atoi
	pop	ebx
	ret
     no_ini_int:
	stc
	ret
  atoi:
	lodsb
	cmp	al,20h
	je	atoi
	cmp	al,9
	je	atoi
	mov	bl,al
	xor	eax,eax
	xor	edx,edx
	cmp	bl,'-'
	je	atoi_digit
	cmp	bl,'+'
	je	atoi_digit
	dec	esi
      atoi_digit:
	mov	dl,[esi]
	sub	dl,30h
	jc	atoi_done
	cmp	dl,9
	ja	atoi_done
	mov	ecx,eax
	shl	ecx,1
	jc	atoi_overflow
	shl	ecx,1
	jc	atoi_overflow
	add	eax,ecx
	shl	eax,1
	jc	atoi_overflow
	js	atoi_overflow
	add	eax,edx
	jc	atoi_overflow
	inc	esi
	jmp	atoi_digit
      atoi_overflow:
	stc
	ret
      atoi_done:
	cmp	bl,'-'
	jne	atoi_sign_ok
	neg	eax
      atoi_sign_ok:
	clc
	ret
  update_ini_value:
	mov	ebp,edx
	mov	esi,[ini_data]
	test	esi,esi
	jz	cannot_update_ini
	call	find_ini_block
	jc	create_ini_block
	call	find_ini_value
	jc	create_ini_value
	mov	edi,esi
	mov	esi,ebp
	jecxz	place_for_ini_value_exhausted
      copy_value_to_ini:
	lodsb
	test	al,al
	jz	shift_rest_of_ini_down
	stosb
	loop	copy_value_to_ini
      place_for_ini_value_exhausted:
	cmp	byte [esi],0
	jne	shift_rest_of_ini_up
	ret
      shift_rest_of_ini_down:
	lea	esi,[edi+ecx]
	neg	ecx
	xchg	ecx,[ini_data_length]
	add	[ini_data_length],ecx
	inc	ecx
	add	ecx,[ini_data]
	sub	ecx,esi
	rep	movsb
	ret
      shift_rest_of_ini_up:
	push	esi edi
	mov	edi,esi
	xor	al,al
	or	ecx,-1
	repne	scasb
	neg	ecx
	sub	ecx,2
	mov	esi,[ini_data]
	add	esi,[ini_data_length]
	mov	edi,esi
	add	edi,ecx
	add	[ini_data_length],ecx
	mov	ebp,ecx
	mov	ecx,esi
	sub	ecx,[esp]
	inc	ecx
	std
	rep	movsb
	cld
	pop	edi esi
	mov	ecx,ebp
	rep	movsb
	ret
      cannot_update_ini:
	ret
      create_ini_block:
	push	edi
	mov	edi,[ini_data]
	mov	ecx,[ini_data_length]
	add	edi,ecx
	jecxz	make_ini_block_header
	mov	ax,0A0Dh
	stosw
      make_ini_block_header:
	mov	al,'['
	stosb
	mov	esi,ebx
	call	copy_str
	mov	al,']'
	stosb
	mov	ax,0A0Dh
	stosw
	pop	esi
      append_ini_value:
	call	copy_str
	mov	al,'='
	stosb
	mov	esi,ebp
	call	copy_str
	mov	ax,0A0Dh
	stosw
	mov	ecx,edi
	sub	ecx,[ini_data]
	mov	[ini_data_length],ecx
	mov	al,1Ah
	stosb
	ret
      copy_str:
	lodsb
	test	al,al
	jz	str_copied
	stosb
	jmp	copy_str
      str_copied:
	ret
      create_ini_value:
	cmp	esi,[ini_data]
	je	ini_value_placement_ok
	dec	esi
	mov	al,[esi]
	cmp	al,20h
	je	create_ini_value
	cmp	al,9
	je	create_ini_value
	cmp	al,0Dh
	je	create_ini_value
	cmp	al,0Ah
	je	create_ini_value
	inc	esi
      find_place_for_ini_value:
	mov	al,[esi]
	lodsb
	cmp	al,0Ah
	je	ini_value_placement_ok
	cmp	al,1Ah
	je	value_at_end_of_ini
	cmp	al,0Dh
	jne	find_place_for_ini_value
	cmp	byte [esi],0Ah
	jne	ini_value_placement_ok
	inc	esi
      ini_value_placement_ok:
	push	edi esi
	xor	al,al
	or	ecx,-1
	repne	scasb
	mov	edi,ebp
	repne	scasb
	neg	ecx
	mov	edi,ecx
	mov	ecx,esi
	neg	ecx
	mov	esi,[ini_data]
	add	esi,[ini_data_length]
	add	[ini_data_length],edi
	add	edi,esi
	add	ecx,esi
	inc	ecx
	std
	rep	movsb
	cld
	pop	edi esi
	call	copy_str
	mov	al,'='
	stosb
	mov	esi,ebp
	call	copy_str
	mov	ax,0A0Dh
	stosw
	ret
      value_at_end_of_ini:
	xchg	esi,edi
	mov	ax,0A0Dh
	stosw
	jmp	append_ini_value

  shutdown:
	call	switch_to_user_screen
	call	load_ini_file
	cmp	[ini_data],0
	je	exit
	mov	ebx,_section_options
	mov	edi,_key_options_securesel
	test	[editor_style],FES_SECURESEL
	setnz	al
	add	al,'0'
	mov	edx,line_buffer
	mov	byte [edx+1],0
	mov	[edx],al
	call	update_ini_value
	mov	edi,_key_options_autobrackets
	test	[editor_style],FES_AUTOBRACKETS
	setnz	al
	add	al,'0'
	mov	edx,line_buffer
	mov	[edx],al
	call	update_ini_value
	mov	edi,_key_options_autoindent
	test	[editor_style],FES_AUTOINDENT
	setnz	al
	add	al,'0'
	mov	edx,line_buffer
	mov	[edx],al
	call	update_ini_value
	mov	edi,_key_options_smarttabs
	test	[editor_style],FES_SMARTTABS
	setnz	al
	add	al,'0'
	mov	edx,line_buffer
	mov	[edx],al
	call	update_ini_value
	mov	edi,_key_options_optimalfill
	test	[editor_style],FES_OPTIMALFILL
	setnz	al
	add	al,'0'
	mov	edx,line_buffer
	mov	[edx],al
	call	update_ini_value
	mov	edx,ini_path
	call	create
	jc	exit
	mov	edx,[ini_data]
	mov	ecx,[ini_data_length]
	call	write
	call	close
      exit:
	mov	ax,4C00h
	int	21h

; Positioning

  update_positions:
	mov	eax,[screen_width]
	mov	[window_width],eax
	mov	eax,[screen_height]
	sub	eax,2
	mov	[window_height],eax
	call	update_window
	ret
  update_cursor:
	xor	bh,bh
	mov	edx,[caret_position]
	sub	edx,[window_position]
	jc	cursor_out_of_sight
	cmp	edx,[window_width]
	jae	cursor_out_of_sight
	mov	eax,[caret_line_number]
	sub	eax,[window_line_number]
	jc	cursor_out_of_sight
	cmp	eax,[window_height]
	jae	cursor_out_of_sight
	inc	al
	mov	dh,al
	mov	ah,2
	int	10h
	test	[editor_mode],FEMODE_OVERWRITE
	jnz	block_cursor
	mov	ah,1
	mov	cx,0D0Eh
	int	10h
	ret
    block_cursor:
	mov	ah,1
	mov	cx,000Fh
	int	10h
	ret
    cursor_out_of_sight:
	mov	ah,1
	mov	cx,1000h
	int	10h
	ret

; Text drawing

  update_screen:
	call	update_title_bar
	mov	eax,[peak_line_length]
	xor	edx,edx
	mov	ebx,SEGMENT_DATA_LENGTH
	div	ebx
	inc	eax
	mul	ebx
	shl	eax,1
	mov	ecx,eax
	cmp	[line_buffer],0
	je	line_buffer_reallocate
	cmp	ecx,[line_buffer_size]
	jbe	line_buffer_ok
	mov	[line_buffer],0
	push	ecx
	mov	ebx,[line_buffer_handle]
	call	release_memory
	pop	ecx
    line_buffer_reallocate:
	mov	[line_buffer_size],ecx
	call	get_memory
	or	eax,eax
	jz	memory_shortage
	mov	[line_buffer],eax
	mov	[line_buffer_handle],ebx
    line_buffer_ok:
	mov	esi,[window_line]
	mov	edx,[window_line_number]
	mov	eax,[video_pitch]
	mov	[screen_offset],eax
	mov	edi,[line_buffer]
    prepare_line:
	add	esi,SEGMENT_HEADER_LENGTH
	mov	ecx,SEGMENT_DATA_LENGTH
	rep	movsb
	mov	esi,[esi-SEGMENT_LENGTH]
	btr	esi,0
	jc	prepare_line
	push	esi edx
	mov	ecx,edi
	mov	esi,[line_buffer]
	sub	ecx,esi
	push	ecx
	mov	al,[text_colors]
	and	al,0Fh
	rep	stosb
	mov	esi,[line_buffer]
	mov	ecx,[esp]
	lea	edi,[esi+ecx]
	call	syntax_proc
    line_prepared:
	mov	edi,screen_row_buffer
	mov	ecx,[window_width]
	mov	al,20h
	mov	ah,[text_colors]
	rep	stosw
	pop	ecx
	mov	esi,[line_buffer]
	lea	ebx,[esi+ecx]
	add	esi,[window_position]
	add	ebx,[window_position]
	sub	ecx,[window_position]
	jbe	text_drawing_ok
	mov	edi,screen_row_buffer
	cmp	ecx,[window_width]
	jbe	draw_text
	mov	ecx,[window_width]
    draw_text:
	movsb
	mov	al,[text_colors]
	and	al,0F0h
	or	al,[ebx]
	stosb
	inc	ebx
	loop	draw_text
    text_drawing_ok:
	mov	edi,screen_row_buffer
	cmp	[selection_line],0
	je	selection_marked
	mov	eax,[selection_line_number]
	cmp	eax,[caret_line_number]
	jne	mark_multiline_selection
	cmp	eax,[esp]
	jne	selection_marked
    mark_simple_selection:
	mov	eax,[selection_position]
	mov	ecx,[caret_position]
	cmp	eax,ecx
	jbe	simple_selection_boundaries_ok
	xchg	eax,ecx
    simple_selection_boundaries_ok:
	sub	ecx,[window_position]
	jbe	selection_marked
	sub	eax,[window_position]
	jae	simple_selection_start_ok
	xor	eax,eax
    simple_selection_start_ok:
	cmp	ecx,[window_width]
	jbe	simple_selection_length_ok
	mov	ecx,[window_width]
    simple_selection_length_ok:
	sub	ecx,eax
	jbe	selection_marked
	lea	edi,[screen_row_buffer+eax*2]
    draw_selection:
	inc	edi
	mov	al,[selection_colors]
	stosb
	loop	draw_selection
	jmp	selection_marked
    mark_multiline_selection:
	test	[editor_mode],FEMODE_VERTICALSEL
	jnz	mark_vertical_selection
	mov	eax,[selection_line_number]
	mov	ebx,[selection_position]
	mov	edx,[caret_line_number]
	mov	ebp,[caret_position]
	cmp	eax,edx
	jbe	multiline_selection_boundaries_ok
	xchg	eax,edx
	xchg	ebx,ebp
    multiline_selection_boundaries_ok:
	mov	edi,screen_row_buffer
	mov	ecx,[window_width]
	cmp	eax,[esp]
	ja	selection_marked
	je	mark_selection_start
	cmp	edx,[esp]
	ja	draw_selection
	jb	selection_marked
    mark_selection_end:
	cmp	ebp,[window_position]
	jbe	selection_marked
	sub	ebp,[window_position]
	cmp	ecx,ebp
	jbe	draw_selection
	mov	ecx,ebp
	jmp	draw_selection
    mark_selection_start:
	sub	ebx,[window_position]
	jbe	draw_selection
	sub	ecx,ebx
	jbe	selection_marked
	lea	edi,[edi+ebx*2]
	jmp	draw_selection
    mark_vertical_selection:
	mov	eax,[selection_line_number]
	mov	edx,[caret_line_number]
	sub	eax,[esp]
	jz	mark_simple_selection
	sub	edx,[esp]
	jz	mark_simple_selection
	xor	eax,edx
	js	mark_simple_selection
    selection_marked:
	push	es gs
	pop	es
	mov	esi,screen_row_buffer
	mov	edi,[screen_offset]
	mov	ecx,[window_width]
	shr	ecx,1
	rep	movsd
	setc	cl
	rep	movsw
	mov	eax,[window_width]
	shl	eax,1
	sub	edi,eax
	add	edi,[video_pitch]
	mov	[screen_offset],edi
	pop	es
	pop	edx esi
	inc	edx
	mov	eax,edx
	sub	eax,[window_line_number]
	cmp	eax,[window_height]
	jae	screen_ok
	mov	edi,[line_buffer]
	or	esi,esi
	jnz	prepare_line
	push	esi edx
	push	[window_position]
	jmp	line_prepared
    screen_ok:
	call	update_status_bar
	ret

  syntax_proc:
	mov	ebx,characters
	xor	edx,edx
    scan_syntax:
	lodsb
    check_character:
	cmp	al,20h
	je	syntax_space
	cmp	al,3Bh
	je	syntax_comment
	mov	ah,al
	xlatb
	or	al,al
	jz	syntax_symbol
	or	edx,edx
	jnz	syntax_neutral
	cmp	ah,27h
	je	syntax_string
	cmp	ah,22h
	je	syntax_string
	cmp	ah,24h
	je	syntax_pascal_hex
	cmp	ah,39h
	ja	syntax_neutral
	cmp	ah,30h
	jae	syntax_number
    syntax_neutral:
	or	edx,-1
	inc	edi
	loop	scan_syntax
	jmp	syntax_done
    syntax_space:
	xor	edx,edx
	inc	edi
	loop	scan_syntax
	jmp	syntax_done
    syntax_symbol:
	mov	al,[symbol_color]
	stosb
	xor	edx,edx
	loop	scan_syntax
	jmp	syntax_done
    syntax_pascal_hex:
	cmp	ecx,1
	je	syntax_neutral
	mov	al,[esi]
	mov	ah,al
	xlatb
	or	al,al
	jz	syntax_neutral
	cmp	ah,24h
	jne	syntax_number
	cmp	ecx,2
	je	syntax_neutral
	mov	al,[esi+1]
	xlatb
	or	al,al
	jz	syntax_neutral
    syntax_number:
	mov	al,[number_color]
	stosb
	loop	number_character
	jmp	syntax_done
    number_character:
	lodsb
	mov	ah,al
	xlatb
	xchg	al,ah
	or	ah,ah
	jz	check_character
	cmp	al,20h
	je	check_character
	cmp	al,3Bh
	je	check_character
	mov	al,[number_color]
	stosb
	loop	number_character
	jmp	syntax_done
    syntax_string:
	mov	al,[string_color]
	stosb
	dec	ecx
	jz	syntax_done
	lodsb
	cmp	al,ah
	jne	syntax_string
	mov	al,[string_color]
	stosb
	dec	ecx
	jz	syntax_done
	lodsb
	cmp	al,ah
	je	syntax_string
	xor	edx,edx
	jmp	check_character
    process_comment:
	lodsb
	cmp	al,20h
	jne	syntax_comment
	inc	edi
	loop	process_comment
	jmp	syntax_done
    syntax_comment:
	mov	al,[comment_color]
	stosb
	loop	process_comment
    syntax_done:
	ret

; Status drawing

  update_status_bar:
	mov	edi,screen_row_buffer
	mov	al,20h
	mov	ecx,[screen_width]
	rep	stosb
	mov	edi,screen_row_buffer+256
	mov	eax,'Row '
	stosd
	mov	eax,[caret_line_number]
	call	number_as_text
	mov	al,'/'
	stosb
	mov	eax,[lines_count]
	call	number_as_text
	mov	eax,', Co'
	stosd
	mov	eax,'lumn'
	stosd
	mov	al,' '
	stosb
	mov	eax,[caret_position]
	inc	eax
	call	number_as_text
	mov	al,'/'
	stosb
	mov	eax,[maximum_position]
	inc	eax
	call	number_as_text
	mov	ecx,edi
	mov	esi,screen_row_buffer+256
	sub	ecx,esi
	mov	eax,[screen_width]
	lea	edi,[screen_row_buffer+eax-1]
	sub	edi,ecx
	mov	byte [edi-2],0B3h
	lea	ebx,[edi-11]
	rep	movsb
	mov	edi,ebx
	sub	ebx,2
	test	[editor_mode],FEMODE_READONLY
	jnz	readonly_status
	mov	eax,[undo_data]
	cmp	eax,[unmodified_state]
	je	editor_status_ok
	mov	eax,'Modi'
	stosd
	mov	eax,'fied'
	stosd
	jmp	editor_status_ok
     readonly_status:
	dec	ebx
	dec	edi
	mov	eax,'Read'
	stosd
	mov	al,'-'
	stosb
	mov	eax,'only'
	stosd
     editor_status_ok:
	mov	byte [ebx],0B3h
	push	ebx
	mov	edi,screen_row_buffer+1
	xor	eax,eax
	mov	edx,[previous_instance]
     count_preceding_instances:
	inc	eax
	or	edx,edx
	jz	preceding_instances_count_ok
	mov	edx,[edx+SEGMENT_HEADER_LENGTH+previous_instance-editor_data]
	jmp	count_preceding_instances
     preceding_instances_count_ok:
	push	eax
	call	number_as_text
	mov	al,'/'
	stosb
	pop	eax
	mov	edx,[next_instance]
     count_following_instances:
	or	edx,edx
	jz	following_instances_count_ok
	inc	eax
	mov	edx,[edx+SEGMENT_HEADER_LENGTH+next_instance-editor_data]
	jmp	count_following_instances
     following_instances_count_ok:
	call	number_as_text
	inc	edi
	mov	al,'-'
	stosb
	inc	edi
	pop	ecx
	sub	ecx,edi
	mov	esi,[file_path]
	call	get_file_title
      print_file_title:
	lodsb
	or	al,al
	jz	editor_title_ok
	stosb
	loop	print_file_title
      editor_title_ok:
	push	es gs
	pop	es
	mov	edi,[video_pitch]
	mov	eax,[screen_height]
	dec	eax
	imul	edi,eax
	mov	esi,screen_row_buffer
	mov	ecx,[screen_width]
	mov	ah,[status_colors]
     draw_status_bar:
	lodsb
	stosw
	loop	draw_status_bar
	pop	es
	ret
     get_file_title:
	or	esi,esi
	jz	untitled
	mov	ebx,esi
      find_file_name:
	lodsb
	or	al,al
	jz	file_title_ok
	cmp	al,'\'
	jne	find_file_name
	mov	ebx,esi
	jmp	find_file_name
      file_title_ok:
	mov	esi,ebx
	ret
      untitled:
	mov	esi,_untitled
	ret
  update_title_bar:
	mov	edi,screen_row_buffer
	mov	al,20h
	mov	ecx,[screen_width]
	sub	ecx,10+1
	rep	stosb
	mov	al,0B3h
	stosb
	mov	esi,_caption
	mov	edi,screen_row_buffer+1
     draw_caption:
	lodsb
	or	al,al
	jz	caption_ok
	stosb
	jmp	draw_caption
     caption_ok:
	mov	edx,[main_project_file]
	or	edx,edx
	jz	main_file_title_ok
	mov	al,20h
	stosb
	mov	al,'-'
	stosb
	mov	al,20h
	stosb
	mov	esi,[file_path]
	cmp	edx,[editor_memory]
	je	get_main_file_title
	mov	esi,[edx+SEGMENT_HEADER_LENGTH+file_path-editor_data]
     get_main_file_title:
	call	get_file_title
	mov	ecx,[screen_width]
	add	ecx,screen_row_buffer-14
	sub	ecx,edi
     print_main_file_title:
	lodsb
	or	al,al
	jz	main_file_title_ok
	stosb
	loop	print_main_file_title
     main_file_title_ok:
	push	es gs
	pop	es
	xor	edi,edi
	mov	esi,screen_row_buffer
	mov	ecx,[screen_width]
	sub	ecx,10
	mov	ah,[status_colors]
     draw_title_bar:
	lodsb
	stosw
	loop	draw_title_bar
	pop	es
	call	update_clock
	ret
  update_clock:
	mov	edi,[screen_width]
	mov	ecx,10
	sub	edi,ecx
	shl	edi,1
	mov	al,[status_colors]
     prepare_clock_colors:
	mov	[gs:edi+(ecx-1)*2+1],al
	loop	prepare_clock_colors
	mov	ah,2Ch
	int	21h
	mov	[gs:edi],byte 20h
	mov	al,ch
	aam
	add	ax,'00'
	mov	[gs:edi+1*2],ah
	mov	[gs:edi+2*2],al
	mov	[gs:edi+3*2],byte ':'
	mov	al,cl
	aam
	add	ax,'00'
	mov	[gs:edi+4*2],ah
	mov	[gs:edi+5*2],al
	mov	[gs:edi+6*2],byte ':'
	mov	al,dh
	aam
	add	ax,'00'
	mov	[gs:edi+7*2],ah
	mov	[gs:edi+8*2],al
	mov	[gs:edi+9*2],byte 20h
	ret
  wait_for_input:
	call	update_clock
	mov	ah,11h
	int	16h
	jz	wait_for_input
	mov	ah,10h
	int	16h
	test	ax,ax
	jz	wait_for_input
	ret
  number_as_text:
	push	ebx
	mov	ecx,1000000000
	xor	edx,edx
	xor	bl,bl
      number_loop:
	div	ecx
	push	edx
	cmp	ecx,1
	je	store_digit
	or	bl,bl
	jnz	store_digit
	or	al,al
	jz	digit_ok
	not	bl
      store_digit:
	add	al,'0'
	stosb
      digit_ok:
	mov	eax,ecx
	xor	edx,edx
	mov	ecx,10
	div	ecx
	mov	ecx,eax
	pop	eax
	or	ecx,ecx
	jnz	number_loop
	pop	ebx
	ret
  sprintf:
	lodsb
	cmp	al,'%'
	je	format_parameter
	stosb
	or	al,al
	jnz	sprintf
	ret
    format_parameter:
	lodsb
	mov	edx,[ebx]
	add	ebx,4
	cmp	al,'s'
	je	insert_string
	cmp	al,'d'
	je	insert_number
	or	al,al
	jnz	sprintf
	dec	esi
	jmp	sprintf
    insert_number:
	push	esi
	mov	eax,edx
	call	number_as_text
	pop	esi
	jmp	sprintf
    insert_string:
	push	esi
	mov	esi,edx
    string_insertion_loop:
	lodsb
	or	al,al
	jz	string_insertion_ok
	stosb
	jmp	string_insertion_loop
    string_insertion_ok:
	pop	esi
	jmp	sprintf

; Windows

  message_box:
	push	eax ebx
	xor	ebp,ebp
	mov	edi,buffer+200h
	mov	dl,[esp+4+3]
	or	dl,dl
	jnz	calculate_buttons_width
	mov	dl,1
	mov	[first_button],_ok
    calculate_buttons_width:
	mov	[buttons_width],0
	mov	eax,[first_button]
	call	add_button_width
	dec	dl
	jz	buttons_width_ok
	add	[buttons_width],2
	mov	eax,[second_button]
	call	add_button_width
	jmp	buttons_width_ok
    add_button_width:
	push	edi
	mov	edi,eax
	xor	al,al
	or	ecx,-1
	repne	scasb
	neg	cl
	add	cl,6-2
	add	[buttons_width],cl
	pop	edi
	ret
    buttons_width_ok:
	mov	al,[buttons_width]
	mov	[message_width],al
    start_message_line:
	mov	ebx,edi
	mov	edx,edi
	mov	ecx,[screen_width]
	sub	ecx,14
	mov	eax,[screen_height]
	sub	eax,7
	inc	ebp
	cmp	ebp,eax
	jae	message_prepared
    copy_message:
	lodsb
	stosb
	cmp	al,20h
	jne	message_character_ok
	mov	edx,edi
    message_character_ok:
	cmp	byte [esi],0
	je	message_prepared
	loop	copy_message
	cmp	edx,ebx
	je	split_word
	lea	eax,[edx-1]
	mov	ecx,[screen_height]
	sub	ecx,7
	inc	ebp
	cmp	ebp,ecx
	je	cut_message
	mov	byte [eax],0Ah
	sub	eax,ebx
	mov	ebx,edx
	mov	ecx,[screen_width]
	lea	ecx,[ecx-14+ebx]
	sub	ecx,edi
	cmp	al,[message_width]
	jbe	copy_message
	mov	[message_width],al
	jmp	copy_message
    cut_message:
	mov	edi,eax
	jmp	message_prepared
    split_word:
	mov	eax,[screen_width]
	sub	eax,14
	mov	[message_width],al
	mov	al,0Ah
	stosb
	jmp	start_message_line
    message_prepared:
	mov	eax,edi
	sub	eax,ebx
	cmp	al,[message_width]
	jbe	message_width_ok
	mov	[message_width],al
    message_width_ok:
	xor	al,al
	stosb
	mov	ecx,ebp
	mov	ch,cl
	add	ch,6
	mov	cl,[message_width]
	add	cl,8
	pop	esi
	mov	ah,[esp+1]
	call	draw_centered_window
	mov	esi,buffer+200h
	add	edi,2*2
    draw_message:
	xor	ecx,ecx
	add	edi,[video_pitch]
    draw_message_row:
	lodsb
	or	al,al
	jz	message_drawn
	cmp	al,0Ah
	je	draw_message
	mov	byte [gs:edi+ecx*2],al
	inc	ecx
	jmp	draw_message_row
    message_drawn:
	add	edi,[video_pitch]
	add	edi,[video_pitch]
	mov	cx,1000h
	mov	ah,1
	int	10h
	movzx	eax,[message_width]
	sub	al,[buttons_width]
	and	al,not 1
	add	edi,eax
	cmp	byte [esp+3],2
	jae	two_button_message
	pop	eax
	mov	ah,al
	mov	esi,[first_button]
	call	draw_button
    wait_for_ok:
	call	wait_for_input
	cmp	ah,1
	je	message_aborted
	cmp	al,20h
	je	message_ok
	cmp	al,0Dh
	jne	wait_for_ok
    message_ok:
	mov	eax,1
	ret
    message_aborted:
	xor	eax,eax
	ret
    two_button_message:
	pop	edx
	xor	cl,cl
	test	edx,10000h
	jnz	two_button_loop
	mov	cl,-1
    two_button_loop:
	push	edi
	mov	al,dl
	and	al,cl
	mov	ah,cl
	not	ah
	and	ah,dh
	or	ah,al
	mov	esi,[first_button]
	call	draw_button
	add	edi,2*2
	mov	al,dh
	and	al,cl
	mov	ah,cl
	not	ah
	and	ah,dl
	or	ah,al
	mov	esi,[second_button]
	call	draw_button
	push	ecx edx
	call	wait_for_input
	pop	edx ecx edi
	cmp	ah,1
	je	message_aborted
	cmp	al,9
	je	two_button_switch
	cmp	ah,0Fh
	je	two_button_switch
	cmp	ah,4Bh
	je	two_button_switch
	cmp	ah,4Dh
	je	two_button_switch
	cmp	ah,48h
	je	two_button_switch
	cmp	ah,50h
	je	two_button_switch
	cmp	al,0Dh
	je	button_selected
	cmp	al,20h
	je	button_selected
	mov	ebx,lower_case_table
	xlatb
	mov	ah,al
	mov	esi,[first_button]
	mov	al,[esi]
	xlatb
	cmp	al,ah
	je	message_ok
	mov	esi,[second_button]
	mov	al,[esi]
	xlatb
	cmp	al,ah
	je	message_second_choice
	jmp	two_button_loop
    button_selected:
	or	cl,cl
	jnz	message_ok
    message_second_choice:
	mov	eax,2
	ret
    two_button_switch:
	not	cl
	jmp	two_button_loop
    draw_button:
	push	es gs
	pop	es
	mov	al,'['
	stosw
	mov	al,20h
	stosw
	stosw
    draw_button_label:
	lodsb
	or	al,al
	jz	button_label_ok
	stosw
	jmp	draw_button_label
    button_label_ok:
	mov	al,20h
	stosw
	stosw
	mov	al,']'
	stosw
	pop	es
	ret
  draw_centered_window:
	mov	dl,byte [screen_width]
	sub	dl,cl
	shr	dl,1
	mov	dh,byte [screen_height]
	sub	dh,ch
	shr	dh,1
	test	[command_flags],80h
	jz	draw_window
	mov	ebx,[caret_line_number]
	sub	ebx,[window_line_number]
	add	ebx,3
	cmp	bl,dh
	jbe	draw_window
	mov	al,dh
	add	al,ch
	add	al,3
	cmp	al,bl
	jb	draw_window
	mov	dh,bl
	movzx	edi,ch
	add	edi,ebx
	add	edi,2
	cmp	edi,[screen_height]
	jb	draw_window
	sub	dh,ch
	sub	dh,4
  draw_window:
	push	es gs
	pop	es
	movzx	edi,dh
	imul	edi,[video_pitch]
	movzx	ebx,dl
	shl	ebx,1
	add	edi,ebx
	movzx	edx,ch
	movzx	ecx,cl
	sub	ecx,4
	sub	edx,2
	push	ecx edi
	mov	al,' '
	stos	word [edi]
	mov	al,'É'
	stos	word [edi]
	mov	al,'Í'
	stos	word [edi]
	dec	ecx
	mov	al,' '
	stos	word [edi]
	dec	ecx
      draw_title:
	lods	byte [esi]
	or	al,al
	jz	title_ok
	stos	word [edi]
	loop	draw_title
	jmp	finish_upper_border
      title_ok:
	mov	al,' '
	stos	word [edi]
	dec	ecx
	jz	finish_upper_border
	mov	al,'Í'
	rep	stos word [edi]
      finish_upper_border:
	mov	al,'»'
	stos	word [edi]
	mov	al,' '
	stos	word [edi]
	pop	edi ecx
	add	edi,[video_pitch]
	lea	ebp,[edi+2*2]
      draw_window_lines:
	push	ecx edi
	mov	al,' '
	stos	word [edi]
	mov	al,'º'
	stos	word [edi]
	mov	al,' '
	rep	stos word [edi]
	mov	al,'º'
	stos	word [edi]
	mov	al,' '
	stos	word [edi]
	mov	byte [es:edi+1],8
	mov	byte [es:edi+3],8
	pop	edi ecx
	add	edi,[video_pitch]
	dec	edx
	jnz	draw_window_lines
	push	ecx edi
	mov	al,' '
	stos	word [edi]
	mov	al,'È'
	stos	word [edi]
	mov	al,'Í'
	rep	stos word [edi]
	mov	al,'¼'
	stos	word [edi]
	mov	al,' '
	stos	word [edi]
	mov	byte [es:edi+1],8
	mov	byte [es:edi+3],8
	pop	edi ecx
	mov	eax,[video_pitch]
	lea	edi,[edi+eax+2*2+1]
	mov	al,8
	add	ecx,4
      finish_bottom_shadow:
	stos	byte [edi]
	inc	edi
	loop	finish_bottom_shadow
	mov	edi,ebp
	mov	eax,edi
	cdq
	idiv	[video_pitch]
	sar	edx,1
	mov	dh,al
	pop	es
	ret
  create_edit_box:
	mov	byte [ebx],1
	mov	[ebx+1],al
	mov	[ebx+2],dx
	mov	[ebx+4],ecx
	xor	eax,eax
	mov	[ebx+8],eax
	mov	[ebx+12],eax
	lea	edi,[ebx+16]
	xor	ecx,ecx
	or	esi,esi
	jz	edit_box_text_ok
      init_edit_box_text:
	lodsb
	or	al,al
	jz	edit_box_text_ok
	stosb
	inc	ecx
	cmp	cx,[ebx+6]
	jb	init_edit_box_text
      edit_box_text_ok:
	mov	[ebx+8],cx
	mov	[ebx+12],cx
	xor	al,al
	stosb
	test	byte [ebx+1],1
	jz	draw_edit_box
    set_edit_box_focus:
	push	ebx
	mov	ah,1
	mov	cx,0D0Eh
	int	10h
	pop	ebx
	jmp	draw_edit_box
    kill_edit_box_focus:
	mov	word [ebx+10],0
	push	ebx
	mov	ah,1
	mov	cx,1000h
	int	10h
	pop	ebx
    draw_edit_box:
	test	byte [ebx+1],1
	jz	edit_box_position_ok
	mov	ax,[ebx+10]
	sub	ax,[ebx+12]
	jae	edit_box_position_correction
	movzx	ax,byte [ebx+4]
	add	ax,[ebx+10]
	sub	ax,2
	sub	ax,[ebx+12]
	jae	edit_box_position_ok
    edit_box_position_correction:
	sub	[ebx+10],ax
    edit_box_position_ok:
	push	es gs
	pop	es
	movzx	edi,byte [ebx+3]
	imul	edi,[video_pitch]
	movzx	eax,byte [ebx+2]
	lea	edi,[edi+eax*2]
	mov	al,20h
	cmp	word [ebx+10],0
	je	edit_box_left_edge_ok
	mov	al,1Bh
      edit_box_left_edge_ok:
	mov	ah,[box_colors]
	stosw
	movzx	eax,word [ebx+10]
	lea	esi,[ebx+16+eax]
	movzx	ebp,byte [ebx+4]
	sub	ebp,2
	mov	edx,[ebx+12]
	cmp	dx,[ebx+14]
	jbe	draw_edit_box_before_selection
	ror	edx,16
      draw_edit_box_before_selection:
	movzx	ecx,dx
	sub	cx,[ebx+10]
	jbe	draw_edit_box_selection
	mov	ah,[box_colors]
	call	draw_edit_box_part
      draw_edit_box_selection:
	mov	ax,dx
	sub	ax,cx
	shr	edx,16
	mov	cx,dx
	sub	cx,ax
	jbe	draw_edit_box_after_selection
	mov	ah,[box_selection_colors]
	test	byte [ebx+1],1
	jnz	edit_box_selection_visible
	mov	ah,[box_colors]
      edit_box_selection_visible:
	call	draw_edit_box_part
      draw_edit_box_after_selection:
	mov	ah,[box_colors]
	mov	cx,[ebx+8]
	sub	cx,dx
	jbe	draw_edit_box_ending
	call	draw_edit_box_part
      draw_edit_box_ending:
	mov	ecx,ebp
	mov	al,20h
	rep	stosw
	movzx	edx,word [ebx+8]
	lea	edx,[ebx+16+edx]
	cmp	esi,edx
	jae	edit_box_right_edge_ok
	mov	al,1Ah
      edit_box_right_edge_ok:
	stosw
	test	byte [ebx+1],1
	jz	edit_box_cursor_ok
	mov	dx,[ebx+2]
	inc	dl
	mov	ax,[ebx+12]
	sub	ax,[ebx+10]
	add	dl,al
	mov	ah,2
	push	ebx
	mov	bh,0
	int	10h
	pop	ebx
      edit_box_cursor_ok:
	pop	es
	ret
      draw_edit_box_part:
	or	bp,bp
	jz	edit_box_part_ok
	cmp	cx,bp
	jbe	edit_box_part_length_ok
	mov	cx,bp
      edit_box_part_length_ok:
	sub	bp,cx
      draw_edit_box_character:
	lodsb
	stosw
	loopw	draw_edit_box_character
      edit_box_part_ok:
	ret
  set_box_focus:
	or	byte [ebx+1],1
	mov	cl,[ebx]
	cmp	cl,1
	jb	set_check_box_focus
	je	set_edit_box_focus
	cmp	cl,2
	je	draw_list_box
	ret
  kill_box_focus:
	and	byte [ebx+1],not 1
	mov	cl,[ebx]
	cmp	cl,1
	je	kill_edit_box_focus
	cmp	cl,2
	je	draw_list_box
	ret
  update_box:
	cmp	byte [ebx],0
	je	update_check_box
	ret
  process_box_command:
	mov	cl,[ebx]
	cmp	cl,1
	jb	check_box_command
	je	edit_box_command
	cmp	cl,2
	je	list_box_command
	stc
	ret
    edit_box_command:
	cmp	al,0E0h
	jne	edit_box_ascii_code
	cmp	ah,4Bh
	je	edit_box_left_key
	cmp	ah,4Dh
	je	edit_box_right_key
	cmp	ah,47h
	je	edit_box_home_key
	cmp	ah,4Fh
	je	edit_box_end_key
	cmp	ah,53h
	je	edit_box_delete
	cmp	ah,52h
	je	edit_box_insert
	cmp	ah,93h
	je	edit_box_ctrl_delete
	cmp	ah,92h
	je	edit_box_ctrl_insert
    edit_box_unknown_command:
	stc
	ret
      edit_box_ascii_code:
	cmp	al,8
	je	edit_box_backspace
	cmp	al,18h
	je	edit_box_cut_block
	cmp	al,3
	je	edit_box_ctrl_insert
	cmp	al,16h
	je	edit_box_paste_block
	cmp	al,20h
	jb	edit_box_unknown_command
	test	byte [ebx+1],100b
	jz	edit_box_ascii_code_ok
	cmp	al,30h
	jb	edit_box_command_done
	cmp	al,39h
	ja	edit_box_command_done
      edit_box_ascii_code_ok:
	mov	dx,word [ebx+12]
	cmp	dx,word [ebx+14]
	je	edit_box_character
	push	eax
	call	edit_box_delete_block
	pop	eax
    edit_box_character:
	call	edit_box_insert_character
	jc	edit_box_command_done
	jmp	edit_box_no_selection
    edit_box_delete:
	test	byte [fs:17h],11b
	jnz	edit_box_cut_block
	mov	dx,word [ebx+12]
	cmp	dx,word [ebx+14]
	jne	edit_box_ctrl_delete
	cmp	dx,[ebx+8]
	je	edit_box_command_done
	inc	dx
	mov	[ebx+14],dx
	jmp	edit_box_ctrl_delete
    edit_box_backspace:
	mov	dx,[ebx+12]
	cmp	dx,word [ebx+14]
	jne	edit_box_ctrl_delete
	or	dx,dx
	jz	edit_box_command_done
	dec	word [ebx+12]
	mov	[ebx+14],dx
    edit_box_ctrl_delete:
	call	edit_box_delete_block
	jmp	edit_box_no_selection
    edit_box_ctrl_insert:
	call	edit_box_copy_block
	jmp	edit_box_command_done
    edit_box_cut_block:
	call	edit_box_copy_block
	call	edit_box_delete_block
	jmp	edit_box_no_selection
    edit_box_insert_character:
	test	byte [ebx+1],100b
	jz	edit_box_character_allowed
	cmp	al,30h
	jb	edit_box_disallowed_character
	cmp	al,39h
	ja	edit_box_disallowed_character
      edit_box_character_allowed:
	movzx	ecx,word [ebx+8]
	cmp	cx,[ebx+6]
	je	edit_box_full
	lea	edi,[ebx+16+ecx]
	lea	esi,[edi-1]
	sub	cx,[ebx+12]
	std
	rep	movsb
	cld
	stosb
	inc	word [ebx+8]
	inc	word [ebx+12]
      edit_box_disallowed_character:
	clc
	ret
      edit_box_full:
	stc
	ret
    edit_box_delete_block:
	movzx	eax,word [ebx+12]
	lea	esi,[ebx+16+eax]
	movzx	eax,word [ebx+14]
	lea	edi,[ebx+16+eax]
	movzx	eax,word [ebx+8]
	lea	ecx,[ebx+16+eax]
	cmp	esi,edi
	jae	edit_box_shift_rest_of_line
	xchg	esi,edi
      edit_box_shift_rest_of_line:
	sub	ecx,esi
	mov	eax,edi
	rep	movsb
	mov	ecx,esi
	sub	ecx,edi
	sub	[ebx+8],cx
	sub	eax,ebx
	sub	eax,16
	mov	[ebx+12],ax
	mov	[ebx+14],ax
	ret
    edit_box_copy_block:
	movzx	ecx,word [ebx+12]
	movzx	edx,word [ebx+14]
	cmp	ecx,edx
	je	edit_box_block_copied
	ja	edit_box_block_start_ok
	xchg	ecx,edx
    edit_box_block_start_ok:
	sub	ecx,edx
	lea	esi,[ebx+16+edx]
	push	ebx esi ecx
	cmp	[clipboard],0
	je	edit_box_allocate_clipboard
	mov	ebx,[clipboard_handle]
	call	release_memory
    edit_box_allocate_clipboard:
	mov	ecx,[esp]
	inc	ecx
	call	get_memory
	mov	[clipboard],eax
	mov	[clipboard_handle],ecx
	or	eax,eax
	jz	not_enough_memory
	mov	edi,eax
	pop	ecx esi ebx
	rep	movsb
	xor	al,al
	stosb
    edit_box_block_copied:
	ret
    edit_box_insert:
	test	byte [fs:17h],11b
	jz	edit_box_command_done
    edit_box_paste_block:
	call	edit_box_delete_block
	mov	esi,[clipboard]
	or	esi,esi
	jz	edit_box_command_done
      edit_box_insert_block:
	lodsb
	or	al,al
	jz	edit_box_no_selection
	cmp	al,0Dh
	je	edit_box_no_selection
	push	esi
	call	edit_box_insert_character
	pop	esi
	jnc	edit_box_insert_block
	jmp	edit_box_no_selection
    edit_box_left_key:
	cmp	word [ebx+12],0
	je	edit_box_no_selection
	dec	word [ebx+12]
	jmp	edit_box_moved_cursor
    edit_box_right_key:
	mov	ax,[ebx+8]
	cmp	[ebx+12],ax
	je	edit_box_no_selection
	inc	word [ebx+12]
	jmp	edit_box_moved_cursor
    edit_box_home_key:
	mov	word [ebx+12],0
	jmp	edit_box_moved_cursor
    edit_box_end_key:
	mov	ax,[ebx+8]
	mov	[ebx+12],ax
	jmp	edit_box_moved_cursor
    edit_box_moved_cursor:
	test	byte [fs:17h],11b
	jnz	edit_box_redraw
    edit_box_no_selection:
	mov	ax,[ebx+12]
	mov	[ebx+14],ax
    edit_box_redraw:
	call	draw_edit_box
    edit_box_command_done:
	movzx	eax,word [ebx+8]
	mov	byte [ebx+16+eax],0
	clc
	ret
  create_list_box:
	mov	byte [ebx],2
	mov	[ebx+1],al
	mov	[ebx+2],dx
	mov	[ebx+4],ecx
	xor	eax,eax
	mov	[ebx+8],eax
	mov	[ebx+12],esi
    draw_list_box:
	mov	ax,[ebx+8]
	sub	ax,[ebx+10]
	jb	list_box_adjust_up
	movzx	dx,byte [ebx+5]
	sub	ax,dx
	jb	list_box_adjustments_ok
	inc	ax
	add	[ebx+10],ax
	jmp	list_box_adjustments_ok
      list_box_adjust_up:
	add	[ebx+10],ax
      list_box_adjustments_ok:
	movzx	edi,byte [ebx+3]
	imul	edi,[video_pitch]
	movzx	ecx,byte [ebx+2]
	lea	edi,[edi+ecx*2]
	movzx	edx,word [ebx+10]
	push	es gs
	pop	es
    draw_list_box_row:
	mov	ah,[box_colors]
	movzx	ecx,byte [ebx+4]
	cmp	dx,[ebx+6]
	jae	draw_empty_list_box_row
	mov	esi,[ebx+12]
	mov	esi,[esi+edx*4]
	test	byte [ebx+1],1
	jz	list_box_row_colors_ok
	cmp	dx,[ebx+8]
	jne	list_box_row_colors_ok
	mov	ah,[box_selection_colors]
      list_box_row_colors_ok:
	sub	ecx,2
	mov	al,20h
	stosw
      draw_list_box_item:
	lodsb
	test	al,al
	jnz	draw_list_box_item_character
	dec	esi
	mov	al,20h
      draw_list_box_item_character:
	stosw
	loop	draw_list_box_item
	mov	al,20h
	cmp	byte [esi],0
	je	list_box_item_ending
	mov	al,1Ah
      list_box_item_ending:
	stosw
	jmp	list_box_row_drawn
    draw_empty_list_box_row:
	mov	al,20h
	rep	stosw
    list_box_row_drawn:
	inc	edx
	mov	ax,dx
	sub	ax,[ebx+10]
	cmp	al,[ebx+5]
	jae	list_box_drawn
	add	edi,[video_pitch]
	movzx	ecx,byte [ebx+4]
	shl	ecx,1
	sub	edi,ecx
	jmp	draw_list_box_row
    list_box_drawn:
	pop	es
	ret
    list_box_command:
	cmp	ah,48h
	je	list_box_up_key
	cmp	ah,50h
	je	list_box_down_key
	cmp	ah,47h
	je	list_box_home_key
	cmp	ah,4Fh
	je	list_box_end_key
	cmp	ah,49h
	je	list_box_pgup_key
	cmp	ah,51h
	je	list_box_pgdn_key
	stc
	ret
    list_box_home_key:
	xor	eax,eax
	mov	[ebx+8],ax
	jmp	list_box_redraw
    list_box_end_key:
	mov	ax,[ebx+6]
	dec	ax
	mov	[ebx+8],ax
	jmp	list_box_redraw
    list_box_pgup_key:
	movzx	ax,byte [ebx+5]
	sub	[ebx+8],ax
	jae	list_box_redraw
	mov	word [ebx+8],0
	jmp	list_box_redraw
    list_box_pgdn_key:
	movzx	ax,byte [ebx+5]
	add	[ebx+8],ax
	mov	ax,[ebx+6]
	dec	ax
	cmp	[ebx+8],ax
	jbe	list_box_redraw
	mov	[ebx+8],ax
	jmp	list_box_redraw
    list_box_up_key:
	mov	ax,[ebx+8]
	sub	ax,1
	jc	list_box_command_done
	dec	word [ebx+8]
	jmp	list_box_redraw
    list_box_down_key:
	mov	ax,[ebx+8]
	inc	ax
	cmp	ax,[ebx+6]
	jae	list_box_command_done
	mov	[ebx+8],ax
    list_box_redraw:
	call	draw_list_box
    list_box_command_done:
	clc
	ret
  create_check_box:
	mov	byte [ebx],0
	mov	[ebx+1],al
	mov	[ebx+2],dx
	mov	[ebx+4],cl
	mov	[ebx+8],ebp
	mov	[ebx+12],edi
	movzx	edx,byte [ebx+3]
	imul	edx,[video_pitch]
	movzx	ecx,byte [ebx+2]
	lea	edx,[edx+ecx*2]
	mov	al,'['
	test	byte [ebx+1],2
	jz	draw_check_box_left_bracket
	mov	al,'('
      draw_check_box_left_bracket:
	mov	byte [gs:edx],al
	add	edx,2
	mov	al,20h
	test	byte [ebx+1],2
	jnz	set_up_radio_initial_state
	test	[edi],ebp
	jz	draw_check_box_initial_state
	mov	al,'+'
	jmp	draw_check_box_initial_state
      set_up_radio_initial_state:
	cmp	[edi],ebp
	jne	draw_check_box_initial_state
	mov	al,7
      draw_check_box_initial_state:
	mov	byte [gs:edx],al
	add	edx,2
	mov	al,']'
	test	byte [ebx+1],2
	jz	draw_check_box_right_bracket
	mov	al,')'
      draw_check_box_right_bracket:
	mov	byte [gs:edx],al
	add	edx,2*2
	movzx	ecx,byte [ebx+4]
      draw_check_box_text:
	lodsb
	or	al,al
	jz	check_box_text_ok
	mov	[gs:edx],al
	add	edx,2
	loop	draw_check_box_text
      check_box_text_ok:
	test	byte [ebx+1],1
	jnz	set_check_box_focus
	ret
    set_check_box_focus:
	push	ebx
	mov	ah,2
	mov	dx,[ebx+2]
	inc	dl
	xor	bh,bh
	int	10h
	mov	ah,1
	mov	cx,0D0Eh
	int	10h
	pop	ebx
	ret
    check_box_command:
	cmp	al,20h
	je	switch_check_box_state
	stc
	ret
    switch_check_box_state:
	mov	edi,[ebx+12]
	mov	eax,[ebx+8]
	test	byte [ebx+1],2
	jnz	set_radio_state
	xor	[edi],eax
	call	update_check_box
	clc
	ret
      set_radio_state:
	mov	[edi],eax
	call	update_check_box
	clc
	ret
    update_check_box:
	movzx	edx,byte [ebx+3]
	imul	edx,[video_pitch]
	movzx	ecx,byte [ebx+2]
	lea	edx,[edx+(ecx+1)*2]
	mov	edi,[ebx+12]
	mov	eax,[ebx+8]
	test	byte [ebx+1],2
	jnz	redraw_radio
	test	[edi],eax
	mov	al,20h
	jz	check_box_state_ok
	mov	al,'+'
      check_box_state_ok:
	mov	byte [gs:edx],al
	ret
      redraw_radio:
	cmp	[edi],eax
	mov	al,20h
	jne	radio_state_ok
	mov	al,7
      radio_state_ok:
	mov	byte [gs:edx],al
	ret

  init_common_dialog:
	xor	eax,eax
	mov	[boxes_count],eax
	mov	[current_box],eax
	ret
  register_box_in_dialog:
	mov	eax,[boxes_count]
	inc	[boxes_count]
	mov	[boxes+eax*4],ebx
	test	byte [ebx+1],1
	jz	box_registered
	mov	[current_box],eax
      box_registered:
	ret
  common_dialog_loop:
	call	wait_for_input
	cmp	ah,1
	je	common_dialog_aborted
	cmp	al,0Dh
	je	common_dialog_ok
	cmp	al,9
	je	common_dialog_cycle_boxes
	cmp	ah,0Fh
	je	common_dialog_reverse_cycle_boxes
	mov	edx,[current_box]
	mov	ebx,[boxes+edx*4]
	call	process_box_command
	jnc	common_dialog_command_processed
	cmp	ah,48h
	je	common_dialog_previous_box
	cmp	ah,50h
	je	common_dialog_next_box
	cmp	ah,4Bh
	je	common_dialog_previous_box
	cmp	ah,4Dh
	je	common_dialog_next_box
	jmp	common_dialog_loop
      common_dialog_command_processed:
	xor	edx,edx
      update_boxes:
	mov	ebx,[boxes+edx*4]
	push	edx
	call	update_box
	pop	edx
	inc	edx
	cmp	edx,[boxes_count]
	jb	update_boxes
	mov	eax,[common_dialog_callback]
	test	eax,eax
	jz	common_dialog_loop
	call	eax
	jmp	common_dialog_loop
      common_dialog_next_box:
	mov	edx,[current_box]
	lea	eax,[edx+1]
	cmp	eax,[boxes_count]
	je	common_dialog_loop
	mov	[current_box],eax
	jmp	common_dialog_switch_box
      common_dialog_previous_box:
	mov	edx,[current_box]
	or	edx,edx
	jz	common_dialog_loop
	dec	[current_box]
	jmp	common_dialog_switch_box
      common_dialog_cycle_boxes:
	mov	edx,[current_box]
	inc	[current_box]
	mov	eax,[current_box]
	cmp	eax,[boxes_count]
	jb	common_dialog_switch_box
	mov	[current_box],0
	jmp	common_dialog_switch_box
      common_dialog_reverse_cycle_boxes:
	mov	edx,[current_box]
	sub	[current_box],1
	jnc	common_dialog_switch_box
	mov	eax,[boxes_count]
	add	[current_box],eax
      common_dialog_switch_box:
	mov	ebx,[boxes+edx*4]
	call	kill_box_focus
	mov	edx,[current_box]
	mov	ebx,[boxes+edx*4]
	call	set_box_focus
	jmp	common_dialog_loop
      common_dialog_ok:
	clc
	ret
      common_dialog_aborted:
	stc
	ret
  get_entered_number:
	xor	edx,edx
      get_digit:
	lodsb
	or	al,al
	jz	entered_number_ok
	sub	al,30h
	movzx	eax,al
	imul	edx,10
	add	edx,eax
	jmp	get_digit
      entered_number_ok:
	ret
  draw_static:
	lodsb
	or	al,al
	jz	fill_static
	mov	[gs:edi],al
	add	edi,2
	loop	draw_static
	ret
      fill_static:
	mov	byte [gs:edi],20h
	add	edi,2
	loop	fill_static
	dec	esi
	ret

  file_open_dialog:
	push	esi
	mov	edi,buffer+3000h
	mov	byte [edi],0
	call	get_current_directory
	cmp	byte [edi-2],'\'
	je	browser_startup_path_ok
	mov	word [edi-1],'\'
      browser_startup_path_ok:
	xor	eax,eax
	mov	[file_list_buffer_handle],eax
	call	make_list_of_files
	pop	esi
	mov	dx,0308h
	mov	cl,35h
	mov	ch,byte [screen_height]
	sub	ch,7
	mov	ah,[window_colors]
	call	draw_window
	push	edx
	mov	eax,[video_pitch]
	mov	edx,[screen_height]
	sub	edx,11
	imul	edx,eax
	lea	edx,[edi+edx+8*2]
	mov	[current_box],edx
	lea	edi,[edi+eax+2*2]
	mov	esi,_file
	mov	ecx,5
	call	draw_static
	mov	ebx,filename_buffer
	xor	esi,esi
	mov	ecx,27h + 256 shl 16
	mov	edx,[esp]
	add	dx,0108h
	mov	al,1
	call	create_edit_box
	mov	ebx,boxes
	mov	esi,[file_list]
	mov	ecx,[file_list_buffer_top]
	sub	ecx,esi
	shl	ecx,16-2
	mov	cl,27h
	mov	ch,byte [screen_height]
	sub	ch,15
	pop	edx
	add	dx,0308h
	xor	al,al
	call	create_list_box
	call	draw_browser_path
      file_input_loop:
	call	wait_for_input
	cmp	ah,1
	je	filename_aborted
	cmp	al,0Dh
	je	filename_accepted
	cmp	ah,0Fh
	je	activate_file_browser
	cmp	ah,50h
	je	activate_file_browser
	mov	ebx,filename_buffer
	call	process_box_command
	jmp	file_input_loop
    activate_file_browser:
	mov	ebx,filename_buffer
	call	kill_box_focus
	mov	ebx,boxes
	call	set_box_focus
	call	update_file_input
      file_browser_loop:
	call	wait_for_input
	cmp	ah,1
	je	filename_aborted
	cmp	al,0Dh
	je	filename_accepted
	cmp	ah,0Fh
	je	activate_file_input
	cmp	ah,4Bh
	je	activate_file_input
	cmp	al,8
	je	go_to_parent_directory
	mov	ebx,boxes
	push	dword [ebx+8]
	call	process_box_command
	pop	eax
	cmp	ax,[ebx+8]
	je	file_browser_loop
	call	update_file_input
	jmp	file_browser_loop
      go_to_parent_directory:
	cmp	byte [buffer+3000h+3],0
	je	file_browser_loop
	mov	edi,buffer
	mov	eax,'..'
	stosd
	jmp	browser_chdir
    filename_accepted:
	mov	edx,filename_buffer+16
	movzx	eax,word [edx-16+8]
	test	eax,eax
	jz	got_filename
	cmp	byte [edx+eax-1],'\'
	je	browser_path_entered
	cmp	byte [edx+eax-1],':'
	jne	got_filename
      browser_path_entered:
	mov	esi,edx
	mov	edi,buffer
      copy_path_to_browse:
	lodsb
	stosb
	test	al,al
	jnz	copy_path_to_browse
	cmp	word [buffer+1],':'
	je	browser_directory_ok
	cmp	byte [edi-2],'\'
	jne	browser_chdir
	mov	byte [edi-2],0
      browser_chdir:
	xor	dx,dx
	mov	ax,713Bh
	call	dos_int
	jnc	browser_directory_ok
	cmp	ax,7100h
	jne	file_list_selection_ok
	mov	ah,3Bh
	call	dos_int
	jc	file_list_selection_ok
      browser_directory_ok:
	cmp	byte [buffer+1],':'
	jne	browser_drive_ok
	mov	dl,[buffer]
	sub	dl,'A'
	cmp	dl,'Z'-'A'
	jbe	browser_change_drive
	sub	dl,'a'-'A'
      browser_change_drive:
	mov	ah,0Eh
	int	21h
      browser_drive_ok:
	push	0
	cmp	dword [buffer],'..'
	jne	name_to_select_ok
	mov	edi,buffer+3000h
	mov	al,'\'
	or	ecx,-1
      find_last_directory_name:
	mov	esi,edi
	repne	scasb
	cmp	byte [edi],0
	jne	find_last_directory_name
	lea	ecx,[edi-1]
	sub	ecx,esi
	mov	edi,buffer+400h
	mov	[esp],ecx
	mov	ebx,upper_case_table
      get_name_to_select:
	lodsb
	xlatb
	stosb
	loop	get_name_to_select
      name_to_select_ok:
	mov	edi,buffer+3000h
	call	get_current_directory
	jc	browser_drive_invalid
	cmp	byte [edi-2],'\'
	je	browser_new_path_ok
	mov	word [edi-1],'\'
      browser_new_path_ok:
	call	make_list_of_files
	call	draw_browser_path
	mov	ebx,filename_buffer
	xor	eax,eax
	mov	[ebx+8],eax
	mov	[ebx+12],eax
	mov	[ebx+16],al
	mov	ebx,boxes
	mov	esi,[file_list]
	mov	[ebx+12],esi
	mov	ecx,[file_list_buffer_top]
	sub	ecx,esi
	shr	ecx,2
	mov	[ebx+6],cx
	xor	eax,eax
	mov	[ebx+8],eax
	mov	eax,esi
	pop	edx
      find_name_to_select:
	cmp	eax,[file_list_buffer_top]
	je	file_list_selection_ok
	mov	esi,[eax]
	add	esi,2
	mov	edi,buffer+400h
	mov	ecx,edx
	repe	cmpsb
	je	select_directory
	add	eax,4
	jmp	find_name_to_select
      select_directory:
	sub	eax,[file_list]
	shr	eax,2
	mov	[ebx+8],ax
      file_list_selection_ok:
	test	byte [filename_buffer+1],1
	jnz	activate_file_input
	jmp	activate_file_browser
      browser_drive_invalid:
	mov	dl,[buffer+3000h]
	sub	dl,'A'
	cmp	dl,'Z'-'A'
	jbe	browser_restore_drive
	sub	dl,'a'-'A'
      browser_restore_drive:
	mov	ah,0Eh
	int	21h
	pop	eax
	jmp	file_list_selection_ok
    got_filename:
	cmp	[filename_buffer+16],0
	je	file_input_loop
	call	release_list_of_files
	mov	edx,filename_buffer+16
	movzx	ecx,word [filename_buffer+8]
	clc
	ret
    filename_aborted:
	call	release_list_of_files
	stc
	ret
    activate_file_input:
	mov	ebx,boxes
	call	kill_box_focus
	mov	ebx,filename_buffer
	call	set_box_focus
	jmp	file_input_loop
    update_file_input:
	mov	ebx,boxes
	mov	esi,[ebx+12]
	movzx	eax,word [ebx+8]
	mov	esi,[esi+eax*4]
	mov	ah,[esi]
	add	esi,2
	mov	edi,filename_buffer+16
      copy_file_item:
	lodsb
	stosb
	test	al,al
	jnz	copy_file_item
	cmp	ah,[browser_symbols+2]
	je	file_item_copied
	cmp	ah,[browser_symbols+3]
	je	file_item_copied
	mov	byte [edi-1],'\'
	stosb
      file_item_copied:
	mov	ecx,edi
	sub	ecx,1+filename_buffer+16
	mov	ebx,filename_buffer
	mov	[ebx+8],cx
	mov	[ebx+12],cx
	xor	eax,eax
	mov	[ebx+10],ax
	mov	[ebx+14],ax
	call	draw_edit_box
	ret
    draw_browser_path:
	mov	edi,[current_box]
	mov	esi,buffer+3000h
	mov	ecx,27h
	call	draw_static
	add	edi,[video_pitch]
	sub	edi,27h*2
	mov	ecx,27h
	call	draw_static
	ret
    make_list_of_files:
	cmp	[file_list_buffer_handle],0
	je	default_buffer_for_file_list
	mov	edi,[file_list_buffer_top]
	mov	ecx,[file_list_buffer_size]
	sub	edi,ecx
	jmp	init_file_list
      default_buffer_for_file_list:
	mov	edi,buffer+1000h
	mov	ecx,2000h
      init_file_list:
	lea	ebx,[edi+ecx]
	mov	[file_list_buffer_top],ebx
	mov	ah,1Ah
	xor	edx,edx
	call	dos_int
	mov	ah,19h
	int	21h
	mov	dl,al
	mov	ah,0Eh
	int	21h
	movzx	ecx,al
	mov	dword [buffer],'A:'
      list_drives:
	push	ecx edi
	mov	ax,290Ch
	xor	esi,esi
	mov	di,10h
	call	dos_int
	pop	edi
	inc	al
	jz	try_next_drive
	cmp	byte [buffer],'B'
	jne	add_drive
	test	byte [fs:10h],11000000b
	jz	try_next_drive
      add_drive:
	sub	ebx,4
	mov	[ebx],edi
	mov	esi,buffer
	mov	ax,2004h
	stosw
	movsw
	movsb
     try_next_drive:
	inc	byte [buffer]
	pop	ecx
	loop	list_drives
	mov	[file_list],ebx
	mov	[file_list_buffer],edi
	cmp	byte [buffer+3000h],0
	je	file_list_made
	mov	edi,buffer
	mov	eax,'*.*'
	stosd
	mov	ax,714Eh
	mov	cx,31h
	xor	esi,esi
	xor	edx,edx
	mov	di,10h
	call	dos_int
	mov	ebx,eax
	jnc	long_file_names_list
	mov	ah,4Eh
	mov	cx,31h
	xor	edx,edx
	call	dos_int
	jc	file_list_made
      short_file_names_list:
	sub	[file_list],4
	mov	edx,[file_list]
	mov	edi,[file_list_buffer]
	cmp	edi,edx
	jae	not_enough_memory_for_list
	mov	[edx],edi
	mov	esi,buffer+1Eh
	test	byte [esi-1Eh+15h],10h
	jnz	short_directory_name
	mov	ebx,lower_case_table
	mov	ax,2003h
	stosw
	jmp	copy_short_file_name
      short_directory_name:
	mov	ebx,upper_case_table
	cmp	word [esi],'..'
	je	short_parent_directory
	cmp	byte [esi],'.'
	je	short_directory_to_hide
	mov	ax,2002h
	stosw
	jmp	copy_short_file_name
      short_parent_directory:
	cmp	byte [buffer+3000h+3],0
	je	short_directory_to_hide
	mov	ax,2001h
	stosw
      copy_short_file_name:
	lodsb
	xlat	byte [ebx]
	cmp	edi,[file_list]
	jae	not_enough_memory_for_list
	stosb
	test	al,al
	jnz	copy_short_file_name
      short_file_name_copied:
	mov	[file_list_buffer],edi
	mov	ah,4Fh
	call	dos_int
	jnc	short_file_names_list
	jmp	file_list_made
      short_directory_to_hide:
	add	[file_list],4
	jmp	short_file_name_copied
      not_enough_memory_for_long_file_name:
	pop	ebx
	mov	ax,71A1h
	call	dos_int
      not_enough_memory_for_list:
	cmp	[file_list_buffer_handle],0
	jne	really_not_enough_memory_for_list
	mov	ax,500h
	mov	edi,buffer
	int	31h
	mov	ecx,[edi]
	cmp	ecx,2000h
	jbe	really_not_enough_memory_for_list
	cmp	ecx,100000h
	jbe	allocate_buffer_for_file_list
	mov	ecx,100000h
      allocate_buffer_for_file_list:
	mov	[file_list_buffer_size],ecx
	call	get_memory
	or	eax,eax
	jz	really_not_enough_memory_for_list
	mov	[file_list_buffer_handle],ebx
	mov	edi,eax
	mov	ecx,[file_list_buffer_size]
	jmp	init_file_list
      really_not_enough_memory_for_list:
	add	[file_list],4
	jmp	file_list_made
      long_file_names_list:
	push	ebx
	sub	[file_list],4
	mov	edx,[file_list]
	mov	edi,[file_list_buffer]
	cmp	edi,edx
	jae	not_enough_memory_for_long_file_name
	mov	[edx],edi
	mov	esi,buffer+10h+2Ch
	test	byte [esi-2Ch],10h
	jnz	long_directory_name
	mov	ax,2003h
	stosw
	mov	ebx,lower_case_table
	jmp	copy_long_file_name
      long_directory_to_hide:
	add	[file_list],4
	jmp	long_file_name_copied
      long_directory_name:
	mov	ebx,upper_case_table
	cmp	byte [esi],'.'
	jne	long_directory_show
	cmp	byte [esi+1],0
	je	long_directory_to_hide
	cmp	word [esi+1],'.'
	jne	long_directory_show
	cmp	byte [buffer+3000h+3],0
	je	long_directory_to_hide
	mov	ax,2001h
	stosw
	jmp	copy_long_file_name
      long_directory_show:
	mov	ax,2002h
	stosw
      copy_long_file_name:
	lodsb
	xlatb
	cmp	edi,[file_list]
	jae	not_enough_memory_for_long_file_name
	stosb
	test	al,al
	jnz	copy_long_file_name
      long_file_name_copied:
	mov	[file_list_buffer],edi
	pop	ebx
	mov	ax,714Fh
	xor	esi,esi
	mov	di,10h
	call	dos_int
	jnc	long_file_names_list
	mov	ax,71A1h
	call	dos_int
      file_list_made:
	mov	edx,[file_list_buffer_top]
	sub	edx,[file_list]
	shr	edx,2
	mov	ebp,edx
      sort_file_list:
	shr	ebp,1
	jz	file_list_sorted
	mov	ebx,ebp
      sorting_iteration:
	cmp	ebx,edx
	jae	sort_file_list
	mov	eax,ebx
      place_into_right_blocks:
	cmp	eax,ebp
	jb	sort_next_offset
	push	edx
	mov	edx,eax
	sub	eax,ebp
	push	eax
	mov	esi,[file_list]
	lea	eax,[esi+eax*4]
	lea	edx,[esi+edx*4]
	mov	esi,[eax]
	mov	edi,[edx]
	mov	ecx,257
	repe	cmpsb
	jbe	exchange_ok
	mov	esi,[eax]
	xchg	esi,[edx]
	mov	[eax],esi
      exchange_ok:
	pop	eax edx
	jmp	place_into_right_blocks
      sort_next_offset:
	inc	ebx
	jmp	sorting_iteration
      file_list_sorted:
	mov	esi,[file_list]
	mov	ebx,browser_symbols
      make_browser_symbols:
	cmp	esi,[file_list_buffer_top]
	je	file_list_done
	mov	edx,[esi]
	mov	al,[edx]
	dec	al
	xlatb
	mov	[edx],al
	add	esi,4
	jmp	make_browser_symbols
      file_list_done:
	ret
    release_list_of_files:
	mov	ebx,[file_list_buffer_handle]
	test	ebx,ebx
	jz	list_of_files_released
	call	release_memory
      list_of_files_released:
	ret
  goto_dialog:
	mov	esi,_position
	mov	dx,080Bh
	mov	cx,0719h
	mov	ah,[window_colors]
	call	draw_window
	push	edx
	push	edi
	mov	eax,[video_pitch]
	lea	edi,[edi+eax+5*2]
	mov	esi,_row
	mov	ecx,4
	call	draw_static
	pop	edi
	mov	eax,[video_pitch]
	lea	eax,[eax*3]
	lea	edi,[edi+eax+2*2]
	mov	esi,_column
	mov	ecx,7
	call	draw_static
	call	init_common_dialog
	mov	edi,buffer+200h
	mov	esi,edi
	mov	eax,[caret_line_number]
	call	number_as_text
	xor	al,al
	stosb
	mov	dx,[esp]
	mov	ebx,buffer
	mov	ecx,9 + 7 shl 16
	add	dx,010Ah
	mov	al,101b
	call	create_edit_box
	call	register_box_in_dialog
	mov	edi,buffer+200h
	mov	esi,edi
	mov	eax,[caret_position]
	inc	eax
	call	number_as_text
	xor	al,al
	stosb
	pop	edx
	mov	ebx,buffer+100h
	mov	ecx,9 + 7 shl 16
	add	dx,030Ah
	mov	al,100b
	call	create_edit_box
	call	register_box_in_dialog
	mov	[common_dialog_callback],0
	call	common_dialog_loop
	jc	goto_dialog_done
	mov	esi,buffer+16
	call	get_entered_number
	mov	ecx,edx
	mov	esi,buffer+100h+16
	call	get_entered_number
	clc
      goto_dialog_done:
	ret
  find_dialog:
	push	[find_flags]
	mov	esi,_find
	mov	dx,050Dh
	mov	cx,0A36h
	mov	ah,[window_colors]
	call	draw_window
	push	edx
	mov	eax,[video_pitch]
	lea	edi,[edi+eax+2*2]
	mov	esi,_text_to_find
	mov	ecx,13
	call	draw_static
	call	init_common_dialog
	call	get_word_at_caret
	mov	edi,[line_buffer]
	mov	esi,[caret_line]
	call	copy_from_line
	xor	al,al
	stosb
	mov	dx,[esp]
	mov	ebx,buffer
	mov	esi,[line_buffer]
	mov	ecx,32 + 1000 shl 16
	add	dx,0110h
	mov	al,1
	call	create_edit_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+800h
	mov	esi,_case_sensitive
	mov	edi,find_flags
	mov	ebp,FEFIND_CASESENSITIVE
	add	dx,0310h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+810h
	mov	esi,_whole_words
	mov	edi,find_flags
	mov	ebp,FEFIND_WHOLEWORDS
	add	dx,0410h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+820h
	mov	esi,_backward
	mov	edi,find_flags
	mov	ebp,FEFIND_BACKWARD
	add	dx,0510h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	pop	edx
	mov	ebx,buffer+830h
	mov	esi,_search_in_whole_text
	mov	edi,find_flags
	mov	ebp,FEFIND_INWHOLETEXT
	add	dx,0610h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	[common_dialog_callback],0
	call	common_dialog_loop
	pop	eax
	jc	find_dialog_aborted
	mov	esi,buffer+16
	mov	eax,[find_flags]
	clc
	ret
      find_dialog_aborted:
	mov	[find_flags],eax
	ret
  replace_dialog:
	push	[find_flags]
	mov	esi,_replace
	mov	dx,050Dh
	mov	cx,0D36h
	mov	ah,[window_colors]
	call	draw_window
	push	edx
	push	edi
	mov	eax,[video_pitch]
	lea	edi,[edi+eax+2*2]
	mov	esi,_text_to_find
	mov	ecx,13
	call	draw_static
	pop	edi
	mov	eax,[video_pitch]
	imul	eax,3
	lea	edi,[edi+eax+6*2]
	mov	esi,_new_text
	mov	ecx,9
	call	draw_static
	call	init_common_dialog
	call	get_word_at_caret
	mov	edi,[line_buffer]
	mov	esi,[caret_line]
	call	copy_from_line
	xor	al,al
	stosb
	mov	dx,[esp]
	mov	ebx,buffer
	mov	esi,[line_buffer]
	mov	ecx,32 + 1000 shl 16
	add	dx,0110h
	mov	al,1
	call	create_edit_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+400h
	xor	esi,esi
	mov	ecx,32 + 1000 shl 16
	add	dx,0310h
	xor	al,al
	call	create_edit_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+800h
	mov	esi,_case_sensitive
	mov	edi,find_flags
	mov	ebp,FEFIND_CASESENSITIVE
	add	dx,0510h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+810h
	mov	esi,_whole_words
	mov	edi,find_flags
	mov	ebp,FEFIND_WHOLEWORDS
	add	dx,0610h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+820h
	mov	esi,_backward
	mov	edi,find_flags
	mov	ebp,FEFIND_BACKWARD
	add	dx,0710h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+830h
	mov	esi,_replace_in_whole_text
	mov	edi,find_flags
	mov	ebp,FEFIND_INWHOLETEXT
	add	dx,0810h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	pop	edx
	mov	ebx,buffer+840h
	mov	esi,_prompt
	mov	edi,command_flags
	mov	ebp,1
	add	dx,0910h
	mov	cl,18h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	[common_dialog_callback],0
	call	common_dialog_loop
	pop	eax
	jc	replace_dialog_aborted
	mov	esi,buffer+16
	mov	edi,buffer+400h+16
	mov	eax,[find_flags]
	clc
	ret
      replace_dialog_aborted:
	mov	[find_flags],eax
	ret
  options_dialog:
	mov	esi,_options
	mov	dx,0616h
	mov	cx,0922h
	mov	ah,[window_colors]
	call	draw_window
	push	edx
	call	init_common_dialog
	mov	ebx,buffer
	mov	esi,_secure_selection
	mov	edi,editor_style
	mov	ebp,FES_SECURESEL
	add	dx,0102h
	mov	cl,16h
	mov	al,1
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+10h
	mov	esi,_auto_brackets
	mov	edi,editor_style
	mov	ebp,FES_AUTOBRACKETS
	add	dx,0202h
	mov	cl,16h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+20h
	mov	esi,_auto_indent
	mov	edi,editor_style
	mov	ebp,FES_AUTOINDENT
	add	dx,0302h
	mov	cl,16h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	dx,[esp]
	mov	ebx,buffer+30h
	mov	esi,_smart_tabs
	mov	edi,editor_style
	mov	ebp,FES_SMARTTABS
	add	dx,0402h
	mov	cl,16h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	pop	edx
	mov	ebx,buffer+40h
	mov	esi,_optimal_fill
	mov	edi,editor_style
	mov	ebp,FES_OPTIMALFILL
	add	dx,0502h
	mov	cl,16h
	xor	al,al
	call	create_check_box
	call	register_box_in_dialog
	mov	[common_dialog_callback],0
	jmp	common_dialog_loop
  ascii_table_window:
	mov	esi,_ascii_table
	mov	dx,0616h
	mov	cx,0C24h
	mov	ah,[window_colors]
	call	draw_window
	push	edx
	mov	ah,[window_colors]
	xor	al,al
	mov	edx,8
      draw_ascii_table:
	mov	ecx,32
      draw_ascii_row:
	mov	[gs:edi],ax
	add	edi,2
	inc	al
	loop	draw_ascii_row
	add	edi,[video_pitch]
	sub	edi,32*2
	dec	edx
	jnz	draw_ascii_table
	mov	ecx,32
      draw_ascii_table_border:
	mov	byte [gs:edi+(ecx-1)*2],'Ä'
	loop	draw_ascii_table_border
	add	edi,[video_pitch]
	push	edi
	mov	ah,1
	mov	cx,000Fh
	int	10h
      ascii_table_update:
	mov	dl,[selected_character]
	mov	dh,dl
	and	dl,11111b
	shr	dh,5
	add	dx,word [esp+4]
	mov	ah,2
	xor	bh,bh
	int	10h
	mov	edi,screen_row_buffer+10h
	mov	eax,'Dec:'
	stosd
	mov	al,20h
	stosb
	movzx	eax,[selected_character]
	call	number_as_text
	mov	al,20h
	stosb
	mov	eax,'Hex:'
	stosd
	mov	al,20h
	stosb
	mov	al,[selected_character]
	shr	al,4
	cmp	al,10
	sbb	al,69h
	das
	stosb
	mov	al,[selected_character]
	and	al,0Fh
	cmp	al,10
	sbb	al,69h
	das
	stosb
	xor	al,al
	stosb
	sub	edi,30+1
	mov	esi,edi
	mov	eax,'Char'
	stosd
	mov	eax,'acte'
	stosd
	mov	eax,'r:  '
	stosd
	mov	ecx,screen_row_buffer+10h
	sub	ecx,edi
	mov	al,20h
	rep	stosb
	mov	edi,[esp]
	add	edi,1*2
	mov	ecx,30
	call	draw_static
	mov	edi,[esp]
	mov	al,[selected_character]
	mov	[gs:edi+12*2],al
      ascii_table_loop:
	call	wait_for_input
	or	ah,ah
	jz	pure_ascii_char
	cmp	ah,48h
	je	ascii_table_up
	cmp	ah,50h
	je	ascii_table_down
	cmp	ah,4Bh
	je	ascii_table_left
	cmp	ah,4Dh
	je	ascii_table_right
	cmp	ah,1
	je	ascii_table_exit
	cmp	al,0E0h
	je	ascii_table_loop
	cmp	al,13
	je	ascii_table_done
	cmp	al,2
	je	ascii_table_done
	cmp	al,20h
	jb	ascii_table_loop
      pure_ascii_char:
	mov	[selected_character],al
	jmp	ascii_table_update
      ascii_table_exit:
	pop	eax eax
	stc
	ret
      ascii_table_done:
	pop	eax eax
	mov	al,[selected_character]
	clc
	ret
      ascii_table_up:
	cmp	[selected_character],20h
	jb	ascii_table_loop
	sub	[selected_character],20h
	jmp	ascii_table_update
      ascii_table_down:
	cmp	[selected_character],0E0h
	jae	ascii_table_loop
	add	[selected_character],20h
	jmp	ascii_table_update
      ascii_table_left:
	test	[selected_character],11111b
	jz	ascii_table_loop
	dec	[selected_character]
	jmp	ascii_table_update
      ascii_table_right:
	mov	al,[selected_character]
	inc	al
	test	al,11111b
	jz	ascii_table_loop
	mov	[selected_character],al
	jmp	ascii_table_update
  calculator_window:
	mov	[results_selection],0
	mov	esi,_calculator
	mov	dx,0602h
	mov	cx,0B4Ch
	mov	ah,[window_colors]
	call	draw_window
	push	edi edx
	mov	eax,[video_pitch]
	lea	edi,[edi+eax+2*2]
	mov	esi,_expression
	mov	ecx,11
	call	draw_static
	mov	eax,[video_pitch]
	lea	eax,[eax*3]
	mov	edi,[esp+4]
	lea	edi,[edi+eax+2*2]
	mov	esi,_result
	mov	ecx,65
	call	draw_static
	call	init_common_dialog
	mov	ebx,buffer
	xor	esi,esi
	mov	ecx,56 + 1000 shl 16
	mov	dx,[esp]
	add	dx,010Eh
	mov	al,1
	call	create_edit_box
	call	register_box_in_dialog
	mov	ebx,buffer+2000h
	mov	esi,_null
	mov	edi,results_selection
	xor	ebp,ebp
	mov	dx,[esp]
	add	dx,0402h
	mov	cl,18h
	mov	al,2
	call	create_check_box
	call	register_box_in_dialog
	mov	ebx,buffer+2010h
	mov	esi,_null
	mov	edi,results_selection
	mov	ebp,1
	mov	dx,[esp]
	add	dx,0502h
	mov	cl,18h
	mov	al,2
	call	create_check_box
	call	register_box_in_dialog
	mov	ebx,buffer+2020h
	mov	esi,_null
	mov	edi,results_selection
	mov	ebp,2
	mov	dx,[esp]
	add	dx,0602h
	mov	cl,18h
	mov	al,2
	call	create_check_box
	call	register_box_in_dialog
	mov	ebx,buffer+2030h
	mov	esi,_null
	mov	edi,results_selection
	mov	ebp,3
	mov	dx,[esp]
	add	dx,0702h
	mov	cl,18h
	mov	al,2
	call	create_check_box
	call	register_box_in_dialog
	pop	edx edi
	mov	eax,[video_pitch]
	lea	edi,[edi+eax*4+6*2]
	mov	[results_offset],edi
	mov	[common_dialog_callback],calculate_result
      calculator_loop:
	call	common_dialog_loop
	jc	close_calculator
	mov	esi,[results_offset]
	mov	eax,[results_selection]
	imul	eax,[video_pitch]
	add	esi,eax
	mov	edi,buffer+16
      copy_result:
	lods	byte [gs:esi]
	cmp	al,20h
	je	result_ready
	stosb
	inc	esi
	jmp	copy_result
      result_ready:
	mov	ecx,edi
	sub	ecx,buffer+16
	mov	ebx,buffer
	mov	[ebx+8],cx
	mov	[ebx+12],cx
	xor	eax,eax
	mov	[ebx+10],ax
	mov	[ebx+14],ax
	cmp	[current_box],0
	jne	activate_expression_box
	call	draw_edit_box
	jmp	calculator_loop
      activate_expression_box:
	mov	edx,[current_box]
	mov	ebx,[boxes+edx*4]
	call	kill_box_focus
	mov	[current_box],0
	mov	ebx,buffer
	call	set_box_focus
	jmp	calculator_loop
      close_calculator:
	ret
      calculate_result:
	mov	esi,buffer+16
	movzx	eax,word [buffer+8]
	lea	edi,[esi+eax]
	xor	eax,eax
	stosb
	mov	[progress_offset],eax
	mov	[source_start],eax
	mov	[hash_tree],eax
	mov	[macro_status],al
	mov	[symbols_file],eax
	mov	[memory_end],buffer+1000h
	mov	[resume_esp],esp
	mov	[resume_eip],calculator_error
	call	convert_line
	push	edi
	call	convert_expression
	cmp	byte [esi],0
	jne	invalid_expression
	mov	al,')'
	stosb
	pop	esi
	mov	[error_line],0
	mov	[current_line],-1
	mov	[value_size],0
	call	calculate_expression
	cmp	[error_line],0
	je	present_result
	jmp	[error]
      present_result:
	mov	ebp,edi
	cmp	byte [ebp+13],0
	je	result_in_64bit_composite_range
	test	byte [ebp+7],80h
	jnz	result_in_64bit_composite_range
	mov	esi,_null
	mov	edi,[results_offset]
	add	edi,[video_pitch]
	mov	ecx,65
	push	edi
	call	draw_static
	pop	edi
	add	edi,[video_pitch]
	mov	ecx,65
	push	edi
	call	draw_static
	pop	edi
	add	edi,[video_pitch]
	mov	ecx,65
	call	draw_static
	jmp	present_decimal
      result_in_64bit_composite_range:
	mov	eax,[ebp]
	mov	edx,[ebp+4]
	mov	edi,buffer+3000h
	mov	word [edi],'b'
      make_binary_number:
	mov	bl,'0'
	shrd	eax,edx,1
	adc	bl,0
	dec	edi
	mov	[edi],bl
	shr	edx,1
	jnz	make_binary_number
	test	eax,eax
	jnz	make_binary_number
	mov	esi,edi
	mov	eax,[video_pitch]
	mov	edi,[results_offset]
	lea	edi,[edi+eax*2]
	mov	ecx,65
	call	draw_static
	mov	ecx,[ebp]
	mov	edx,[ebp+4]
	mov	edi,buffer+3000h
	mov	word [edi],'o'
      make_octal_number:
	mov	al,cl
	and	al,111b
	add	al,'0'
	dec	edi
	mov	[edi],al
	shrd	ecx,edx,3
	shr	edx,3
	jnz	make_octal_number
	test	ecx,ecx
	jnz	make_octal_number
	mov	esi,edi
	mov	eax,[video_pitch]
	mov	edi,[results_offset]
	lea	eax,[eax*3]
	add	edi,eax
	mov	ecx,65
	call	draw_static
	mov	ecx,[ebp]
	mov	edx,[ebp+4]
	mov	edi,buffer+3000h
	mov	word [edi],'h'
      make_hexadecimal_number:
	mov	al,cl
	and	al,0Fh
	cmp	al,10
	sbb	al,69h
	das
	dec	edi
	mov	[edi],al
	shrd	ecx,edx,4
	shr	edx,4
	jnz	make_hexadecimal_number
	test	ecx,ecx
	jnz	make_hexadecimal_number
	cmp	al,'A'
	jb	hexadecimal_number_ok
	dec	edi
	mov	byte [edi],'0'
      hexadecimal_number_ok:
	mov	esi,edi
	mov	eax,[video_pitch]
	mov	edi,[results_offset]
	lea	edi,[edi+eax]
	mov	ecx,65
	call	draw_static
      present_decimal:
	mov	edi,buffer+3000h
	mov	byte [edi],0
	mov	ecx,10
	xor	bl,bl
	cmp	byte [ebp+13],0
	je	make_decimal_number
	mov	bl,'-'
	mov	eax,[ebp]
	mov	edx,[ebp+4]
	not	eax
	not	edx
	add	eax,1
	adc	edx,0
	mov	[ebp],eax
	mov	[ebp+4],edx
	or	eax,edx
	jnz	make_decimal_number
	dec	edi
	mov	byte [edi],'6'
	mov	dword [ebp],99999999h
	mov	dword [ebp+4],19999999h
      make_decimal_number:
	mov	eax,[ebp+4]
	xor	edx,edx
	div	ecx
	mov	[ebp+4],eax
	mov	eax,[ebp]
	div	ecx
	mov	[ebp],eax
	add	dl,'0'
	dec	edi
	mov	[edi],dl
	or	eax,[ebp+4]
	jnz	make_decimal_number
	test	bl,bl
	jz	decimal_number_ok
	dec	edi
	mov	[edi],bl
      decimal_number_ok:
	mov	esi,edi
	mov	edi,[results_offset]
	mov	ecx,65
	call	draw_static
	ret
      calculator_error:
	mov	ebx,[video_pitch]
	mov	ebp,[results_offset]
	mov	edx,4
      clear_results:
	mov	ecx,65
	mov	edi,ebp
	call	fill_static
	add	ebp,ebx
	dec	edx
	jnz	clear_results
	ret

; Memory allocation

  get_memory:
	push	esi edi
	mov	ebx,ecx
	shr	ebx,16
	mov	ax,501h
	int	31h
	jc	dpmi_allocation_failed
	mov	ax,bx
	shl	eax,16
	mov	ax,cx
	mov	edx,main
	shl	edx,4
	sub	eax,edx
	mov	bx,si
	shl	ebx,16
	mov	bx,di
	pop	edi esi
	ret
    dpmi_allocation_failed:
	xor	eax,eax
	pop	edi esi
	ret
  release_memory:
	push	esi edi
	mov	esi,ebx
	shr	esi,16
	mov	di,bx
	mov	ax,502h
	int	31h
	pop	edi esi
	ret
  get_low_memory:
	mov	ax,100h
	mov	bx,-1
	int	31h
	movzx	eax,bx
	shl	eax,4
	mov	[low_memory_size],eax
	mov	ax,100h
	int	31h
	mov	[low_memory_selector],dx
	jnc	low_memory_ok
	xor	edx,edx
	mov	[low_memory_size],edx
      low_memory_ok:
	ret
  release_low_memory:
	cmp	[low_memory_size],0
	je	low_memory_ok
	mov	ax,101h
	mov	dx,[low_memory_selector]
	int	31h
	ret

; File operations

  dos_int:
	push	0 0 0
	pushw	buffer_segment buffer_segment
	stc
	pushfw
	push	eax
	push	ecx
	push	edx
	push	ebx
	push	0
	push	ebp
	push	esi
	push	edi
	mov	ax,300h
	mov	bx,21h
	xor	cx,cx
	mov	edi,esp
	push	es ss
	pop	es
	int	31h
	pop	es
	mov	edi,[esp]
	mov	esi,[esp+4]
	mov	ebp,[esp+8]
	mov	ebx,[esp+10h]
	mov	edx,[esp+14h]
	mov	ecx,[esp+18h]
	mov	ah,[esp+20h]
	add	esp,32h
	sahf
	mov	eax,[esp-32h+1Ch]
	ret
  open:
	push	esi edi
	call	adapt_path
	mov	ax,716Ch
	mov	bx,100000b
	mov	dx,1
	xor	cx,cx
	xor	si,si
	call	dos_int
	jnc	open_done
	cmp	ax,7100h
	je	old_open
	stc
	jmp	open_done
      old_open:
	mov	ax,3D00h
	xor	dx,dx
	call	dos_int
      open_done:
	mov	bx,ax
	pop	edi esi
	ret
    adapt_path:
	mov	esi,edx
	mov	edi,buffer
      copy_path:
	lodsb
	cmp	al,'/'
	jne	path_char_ok
	mov	al,'\'
      path_char_ok:
	stosb
	or	al,al
	jnz	copy_path
	ret
  create:
	push	esi edi
	call	adapt_path
	mov	ax,716Ch
	mov	bx,100001b
	mov	dx,10010b
	xor	cx,cx
	xor	si,si
	xor	di,di
	call	dos_int
	jnc	create_done
	cmp	ax,7100h
	je	old_create
	stc
	jmp	create_done
    old_create:
	mov	ah,3Ch
	xor	cx,cx
	xor	dx,dx
	call	dos_int
    create_done:
	mov	bx,ax
	pop	edi esi
	ret
  write:
	push	edx esi edi ebp
	mov	ebp,ecx
	mov	esi,edx
      write_loop:
	mov	ecx,1000h
	sub	ebp,1000h
	jnc	do_write
	add	ebp,1000h
	mov	ecx,ebp
	xor	ebp,ebp
      do_write:
	push	ecx
	mov	edi,buffer
	shr	ecx,2
	rep	movsd
	mov	ecx,[esp]
	and	ecx,11b
	rep	movsb
	pop	ecx
	mov	ah,40h
	xor	dx,dx
	call	dos_int
	or	ebp,ebp
	jnz	write_loop
	pop	ebp edi esi edx
	ret
  read:
	push	edx esi edi ebp
	mov	ebp,ecx
	mov	edi,edx
      read_loop:
	mov	ecx,1000h
	sub	ebp,1000h
	jnc	do_read
	add	ebp,1000h
	mov	ecx,ebp
	xor	ebp,ebp
      do_read:
	push	ecx
	mov	ah,3Fh
	xor	dx,dx
	call	dos_int
	cmp	ax,cx
	jne	eof
	mov	esi,buffer
	mov	ecx,[esp]
	shr	ecx,2
	rep	movsd
	pop	ecx
	and	ecx,11b
	rep	movsb
	or	ebp,ebp
	jnz	read_loop
      read_done:
	pop	ebp edi esi edx
	ret
      eof:
	pop	ecx
	stc
	jmp	read_done
  close:
	mov	ah,3Eh
	int	21h
	ret
  lseek:
	mov	ah,42h
	mov	ecx,edx
	shr	ecx,16
	int	21h
	pushf
	shl	edx,16
	popf
	mov	dx,ax
	mov	eax,edx
	ret

; Other functions needed by assembler core

  get_environment_variable:
	push	esi edi
	mov	ebx,_section_environment
	call	get_ini_value
	pop	edi ebx
	jnc	found_value_in_ini
	push	ds
	mov	ds,[environment_selector]
	xor	esi,esi
      compare_variable_names:
	mov	edx,ebx
      compare_name_char:
	lodsb
	mov	ah,[es:edx]
	inc	edx
	cmp	al,'='
	je	end_of_variable_name
	or	ah,ah
	jz	next_variable
	sub	ah,al
	jz	compare_name_char
	cmp	ah,20h
	jne	next_variable
	cmp	al,41h
	jb	next_variable
	cmp	al,5Ah
	jna	compare_name_char
      next_variable:
	lodsb
	or	al,al
	jnz	next_variable
	cmp	byte [esi],0
	jne	compare_variable_names
	pop	ds
	ret
      end_of_variable_name:
	or	ah,ah
	jnz	next_variable
      copy_variable_value:
	lodsb
	cmp	edi,[es:memory_end]
	jae	out_of_memory
	stosb
	or	al,al
	jnz	copy_variable_value
	dec	edi
	pop	ds
	ret
      found_value_in_ini:
	lea	eax,[edi+ecx]
	cmp	eax,[memory_end]
	jae	out_of_memory
	rep	movsb
	ret
  make_timestamp:
	mov	ah,2Ah
	int	21h
	push	dx cx
	movzx	ecx,cx
	mov	eax,ecx
	sub	eax,1970
	mov	ebx,365
	mul	ebx
	mov	ebp,eax
	mov	eax,ecx
	sub	eax,1969
	shr	eax,2
	add	ebp,eax
	mov	eax,ecx
	sub	eax,1901
	mov	ebx,100
	div	ebx
	sub	ebp,eax
	mov	eax,ecx
	xor	edx,edx
	sub	eax,1601
	mov	ebx,400
	div	ebx
	add	ebp,eax
	movzx	ecx,byte [esp+3]
	mov	eax,ecx
	dec	eax
	mov	ebx,30
	mul	ebx
	add	ebp,eax
	cmp	ecx,8
	jbe	months_correction
	mov	eax,ecx
	sub	eax,7
	shr	eax,1
	add	ebp,eax
	mov	ecx,8
      months_correction:
	mov	eax,ecx
	shr	eax,1
	add	ebp,eax
	cmp	ecx,2
	pop	cx
	jbe	day_correction_ok
	sub	ebp,2
	test	ecx,11b
	jnz	day_correction_ok
	xor	edx,edx
	mov	eax,ecx
	mov	ebx,100
	div	ebx
	or	edx,edx
	jnz	day_correction
	mov	eax,ecx
	mov	ebx,400
	div	ebx
	or	edx,edx
	jnz	day_correction_ok
      day_correction:
	inc	ebp
      day_correction_ok:
	pop	dx
	movzx	eax,dl
	dec	eax
	add	eax,ebp
	mov	ebx,24
	mul	ebx
	push	eax
	mov	ah,2Ch
	int	21h
	pop	eax
	push	dx
	movzx	ebx,ch
	add	eax,ebx
	mov	ebx,60
	mul	ebx
	movzx	ebx,cl
	add	eax,ebx
	mov	ebx,60
	mul	ebx
	pop	bx
	movzx	ebx,bh
	add	eax,ebx
	adc	edx,0
	ret
  display_block:
	mov	edi,[display_length]
	mov	eax,[display_length]
	add	eax,ecx
	cmp	eax,[low_memory_size]
	ja	not_enough_memory
	mov	[display_length],eax
	push	es
	mov	es,[low_memory_selector]
	rep	movsb
	pop	es
	ret

; Error handling

  not_enough_memory:
	call	update_screen
	mov	esi,_memory_error
	mov	ebx,_error
	movzx	eax,[error_box_colors]
	call	message_box
	mov	esp,stack_top
	jmp	main_loop

  fatal_error:
	cmp	[progress_offset],0
	je	error_outside_compiler
	pop	esi
	mov	esp,stack_top
	push	esi
	mov	ax,205h
	mov	bl,9
	mov	edx,dword [keyboard_handler]
	mov	cx,word [keyboard_handler+4]
	int	31h
	mov	ebx,[allocated_memory]
	call	release_memory
	call	update_screen
      show_error_summary:
	mov	esi,buffer+3000h
	call	go_to_directory
	mov	esi,_assembler_error
	mov	edi,buffer
	mov	ebx,esp
	call	sprintf
	mov	esi,buffer
	mov	ebx,_compile
	movzx	eax,[error_box_colors]
	mov	[first_button],_ok
	mov	[second_button],_get_display
	cmp	[display_length],0
	je	show_compilation_summary
	or	eax,2000000h
	jmp	show_compilation_summary
  assembler_error:
	cmp	[progress_offset],0
	je	error_outside_compiler
	pop	esi
	mov	esp,stack_top
	push	esi
	mov	ax,205h
	mov	bl,9
	mov	edx,dword [keyboard_handler]
	mov	cx,word [keyboard_handler+4]
	int	31h
	and	[output_file],0
	call	show_display_buffer
	call	update_screen
	mov	ebx,[current_line]
      find_error_origin:
	test	dword [ebx+4],80000000h
	jz	error_origin_found
	mov	ebx,[ebx+8]
	jmp	find_error_origin
      error_origin_found:
	mov	esi,[ebx]
	mov	edi,filename_buffer
      copy_error_file:
	lodsb
	stosb
	or	al,al
	jnz	copy_error_file
	push	dword [ebx+4]
	mov	ebx,[allocated_memory]
	call	release_memory
	mov	edx,filename_buffer
	call	load_file
      show_error_line:
	pop	eax
	call	find_line
	xor	eax,eax
	mov	[selection_line],esi
	mov	[selection_line_number],ecx
	mov	[selection_position],eax
	mov	[caret_position],eax
	push	esi
	lea	edi,[esi+SEGMENT_HEADER_LENGTH]
	lea	ebp,[esi+SEGMENT_LENGTH]
	mov	ebx,characters
	xor	edx,edx
      check_for_more_lines:
	call	peek_character
	jc	no_more_lines
	cmp	al,3Bh
	je	no_more_lines
	mov	ah,al
	xlatb
	or	al,al
	jz	symbol
	or	edx,edx
	jnz	neutral
	cmp	ah,27h
	je	quoted
	cmp	ah,22h
	je	quoted
      neutral:
	or	edx,-1
	jmp	check_for_more_lines
      peek_character:
	cmp	edi,ebp
	je	peek_next_segment
	mov	al,[edi]
	inc	edi
	clc
	ret
      peek_next_segment:
	mov	esi,[esi]
	btr	esi,0
	lea	edi,[esi+SEGMENT_HEADER_LENGTH]
	lea	ebp,[esi+SEGMENT_LENGTH]
	jc	peek_character
	stc
	ret
      symbol:
	cmp	ah,'\'
	je	backslash
	xor	edx,edx
	jmp	check_for_more_lines
      quoted:
	call	peek_character
	jc	no_more_lines
	cmp	al,ah
	jne	quoted
	call	peek_character
	jc	no_more_lines
	cmp	al,ah
	je	quoted
	dec	edi
	xor	edx,edx
	jmp	check_for_more_lines
      backslash:
	call	peek_character
	jc	more_lines
	cmp	al,20h
	je	backslash
	cmp	al,3Bh
	jne	no_more_lines
      comment:
	mov	esi,[esi]
	btr	esi,0
	jc	comment
      more_lines:
	or	esi,esi
	jz	last_line
	inc	ecx
	mov	[esp],esi
	jmp	check_for_more_lines
      last_line:
	pop	[caret_line]
	mov	[caret_line_number],ecx
	mov	eax,[maximum_position]
	mov	[caret_position],eax
	jmp	error_line_highlighted
      no_more_lines:
	or	esi,esi
	jz	last_line
	pop	eax
	inc	ecx
	mov	[caret_line],esi
	mov	[caret_line_number],ecx
      error_line_highlighted:
	call	let_caret_appear
	mov	eax,[caret_line]
	xchg	eax,[selection_line]
	mov	[caret_line],eax
	mov	eax,[caret_line_number]
	xchg	eax,[selection_line_number]
	mov	[caret_line_number],eax
	mov	eax,[caret_position]
	xchg	eax,[selection_position]
	mov	[caret_position],eax
	call	let_caret_appear
	call	update_window
	call	update_screen
	jmp	show_error_summary
      error_outside_compiler:
	mov	esp,[resume_esp]
	jmp	[resume_eip]

; Assembler core

  include '..\..\errors.inc'
  include '..\..\symbdump.inc'
  include '..\..\preproce.inc'
  include '..\..\parser.inc'
  include '..\..\exprpars.inc'
  include '..\..\assemble.inc'
  include '..\..\exprcalc.inc'
  include '..\..\formats.inc'
  include '..\..\x86_64.inc'
  include '..\..\avx.inc'

; Assembler constants

  include '..\..\tables.inc'
  include '..\..\messages.inc'
  include '..\..\version.inc'

; String constants

  _caption db 'flat assembler ',VERSION_STRING,0
  _copyright db 'Copyright (c) 1999-2018, Tomasz Grysztar',0

  _null db 0
  _untitled db 'Untitled',0
  _compile db 'Compile',0
  _error db 'Error',0
  _ok db 'OK',0
  _yes db 'Yes',0
  _no db 'No',0
  _get_display db 'Get display to clipboard',0
  _open db 'Open',0
  _save_as db 'Save as',0
  _file db 'File:',0
  _position db 'Position',0
  _row db 'Row:',0
  _column db 'Column:',0
  _find db 'Find',0
  _replace db 'Replace',0
  _text_to_find db 'Text to find:',0
  _new_text db 'New text:',0
  _expression db 'Expression:',0
  _result db 'Result:',0
  _case_sensitive db 'Case sensitive',0
  _whole_words db 'Whole words',0
  _backward db 'Backward search',0
  _search_in_whole_text db 'Search in whole text',0
  _replace_in_whole_text db 'Replace in whole text',0
  _prompt db 'Prompt on replace',0
  _options db 'Editor options',0
  _secure_selection db 'Secure selection',0
  _auto_brackets db 'Automatic brackets',0
  _auto_indent db 'Automatic indents',0
  _smart_tabs db 'Smart tabulation',0
  _optimal_fill db 'Optimal fill on saving',0
  _ascii_table db 'ASCII table',0
  _calculator db 'Calculator',0

  _startup_failed db 'Failed to allocate required memory.',0
  _memory_error db 'Not enough memory to complete this operation.',0
  _loading_error db 'Could not load file %s.',0
  _saving_error db 'Could not write file to disk.',0
  _not_executable db 'Cannot execute this kind of file.',0
  _saving_question db 'File was modified. Save it now?',0
  _overwrite_question db 'File %s already exists. Do you want to replace it?',0
  _directory_question db 'Directory %s does not exist. Do you want to create it now?',0
  _directory_error db 'Failed to create the directory.',0
  _invalid_path db 'Invalid path.',0
  _not_found_after db 'Text %s not found after current position.',0
  _not_found_before db 'Text %s not found before current position.',0
  _replace_prompt db 'Replace this occurence?',0
  _replaces_made db '%d replaces made.',0
  _assembler_error db 'Error: %s.',0

  _section_environment db 'Environment',0
  _section_compiler db 'Compiler',0
  _key_compiler_memory db 'Memory',0
  _key_compiler_passes db 'Passes',0
  _section_options db 'Options',0
  _key_options_securesel db 'SecureSelection',0
  _key_options_autobrackets db 'AutoBrackets',0
  _key_options_autoindent db 'AutoIndent',0
  _key_options_smarttabs db 'SmartTabs',0
  _key_options_optimalfill db 'OptimalFill',0
  _section_colors db 'Colors',0
  _key_color_text db 'Text',0
  _key_color_background db 'Background',0
  _key_color_seltext db 'SelectionText',0
  _key_color_selbackground db 'SelectionBackground',0
  _key_color_symbols db 'Symbols',0
  _key_color_numbers db 'Numbers',0
  _key_color_strings db 'Strings',0
  _key_color_comments db 'Comments',0
  _key_color_statustext db 'StatusText',0
  _key_color_statusbackground db 'StatusBackground',0
  _key_color_wintext db 'WindowText',0
  _key_color_winbackground db 'WindowBackground',0
  _key_color_msgtext db 'MessageText',0
  _key_color_msgbackground db 'MessageBackground',0
  _key_color_msgseltext db 'MessageSelectionText',0
  _key_color_msgselbackground db 'MessageSelectionBackground',0
  _key_color_errtext db 'ErrorText',0
  _key_color_errbackground db 'ErrorBackground',0
  _key_color_errseltext db 'ErrorSelectionText',0
  _key_color_errselbackground db 'ErrorSelectionBackground',0
  _key_color_boxtext db 'BoxText',0
  _key_color_boxbackground db 'BoxBackground',0
  _key_color_boxseltext db 'BoxSelectionText',0
  _key_color_boxselbackground db 'BoxSelectionBackground',0

; Configuration

  editor_style dd FES_AUTOINDENT+FES_SMARTTABS+FES_SECURESEL+FES_OPTIMALFILL

  text_colors db 87h
  selection_colors db 7Fh
  symbol_color db 0Fh
  number_color db 0Ah
  string_color db 0Ch
  comment_color db 3
  status_colors db 2Fh
  window_colors db 3Fh
  box_colors db 1Fh
  box_selection_colors db 9Fh
  message_box_colors dw 3F1Fh
  error_box_colors dw 4E6Eh

; Other constants

  browser_symbols db 18h,09h,07h,0F0h

; Editor core

  include '..\memory.inc'
  include '..\navigate.inc'
  include '..\edit.inc'
  include '..\blocks.inc'
  include '..\search.inc'
  include '..\undo.inc'

; Editor constants

  SEGMENT_LENGTH	= 160
  BLOCK_LENGTH		= 1024 * SEGMENT_LENGTH
  SEGMENT_HEADER_LENGTH = 16
  SEGMENT_DATA_LENGTH	= SEGMENT_LENGTH - SEGMENT_HEADER_LENGTH

  FEMODE_OVERWRITE   = 1
  FEMODE_VERTICALSEL = 2
  FEMODE_NOUNDO      = 4
  FEMODE_READONLY    = 8

  FEFIND_CASESENSITIVE = 1
  FEFIND_WHOLEWORDS    = 2
  FEFIND_BACKWARD      = 4
  FEFIND_INWHOLETEXT   = 8

  FES_AUTOINDENT   = 0001h
  FES_AUTOBRACKETS = 0002h
  FES_SMARTTABS    = 0004h
  FES_SECURESEL    = 0008h
  FES_OPTIMALFILL  = 0010h

  include '..\version.inc'

; Editor data

  editor_data:

  next_instance dd ?
  previous_instance dd ?
  file_path dd ?
  file_path_handle dd ?

  include '..\variable.inc'

  editor_data_size = $ - editor_data

  if editor_data_size > SEGMENT_DATA_LENGTH
    err
  end if

  lower_case_table db 100h dup ?
  upper_case_table db 100h dup ?

; Assembler core data

  include '..\..\variable.inc'

; Interface specific data

  psp_selector dw ?
  environment_selector dw ?
  main_selector dw ?
  bios_selector dw ?
  video_selector dw ?

  screen_width dd ?
  screen_height dd ?
  video_pitch dd ?

  video_storage dd ?
  video_storage_handle dd ?
  stored_cursor dw ?
  stored_cursor_position dw ?
  stored_page db ?
  stored_mode db ?

  low_memory_size dd ?
  low_memory_selector dw ?

  last_operation db ?
  current_operation db ?
  was_selection db ?

  line_buffer dd ?
  line_buffer_size dd ?
  line_buffer_handle dd ?
  screen_offset dd ?
  screen_row_buffer db 512 dup ?

  clipboard dd ?
  clipboard_handle dd ?

  main_project_file dd ?
  memory_limit dd ?
  allocated_memory dd ?
  start_time dd ?
  progress_offset dd ?
  keyboard_handler dp ?
  display_length dd ?

  find_flags dd ?
  replaces_count dd ?
  selected_character db ?
  command_flags db ?
  message_width db ?
  buttons_width db ?
  first_button dd ?
  second_button dd ?

  file_handle dd ?
  filename_buffer db 17+256 dup ?

  ini_data dd ?
  ini_data_handle dd ?
  ini_data_length dd ?
  ini_path db 260 dup ?

  file_list dd ?
  file_list_buffer dd ?
  file_list_buffer_top dd ?
  file_list_buffer_handle dd ?
  file_list_buffer_size dd ?

  current_box dd ?
  boxes_count dd ?
  boxes dd 16 dup ?
  common_dialog_callback dd ?

  resume_esp dd ?
  resume_eip dd ?
  results_offset dd ?
  results_selection dd ?

segment buffer_segment

  buffer = (buffer_segment-main) shl 4

  db 4000h dup ?

segment stack_segment

  stack_bottom = (stack_segment-main) shl 4

  db 4000h dup ?

  stack_top = stack_bottom + $
