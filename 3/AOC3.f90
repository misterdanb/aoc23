program AOC3
    implicit none

    ! Define an array of strings of length 1024 each
    character(len=140), dimension(140) :: lines

    ! Define the iostat ios
    integer :: ios, i, j, k, l

    ! Array of start and end positions of the part numbers
    integer, dimension(100000, 3) :: parts
    logical :: part_started, part_connected
    character(len=140) :: part_number_string
    integer :: part_number, last_part, parts_sum, sum_gear_ratios

    ! Define a gear type with two integer coordinates
    type :: gear
        integer :: x
        integer :: y
        integer :: part_number
        logical :: connected
    end type gear

    type(gear), dimension(100000) :: parts_with_gear

    ! Opens the file with the name 'input' and reads it line by line and
    ! stores it in the array lines, ignore the iostat
    open(unit=10, file='input', status='old', action='read', iostat=ios)
    do i=1,140
        read(10, '(A)', iostat=ios) lines(i)
    end do
    close(10)

    ! Write all lines to the screen
    do i=1,140
        write(*, '(A)') lines(i)
    end do

    ! Loop through the lines and for each line loop through all the characters
    part_started = .false.
    k = 1
    do i=1,140
        do j=1,140
            ! Check if the character a digit
            if (lines(i)(j:j) .ge. '0' .and. lines(i)(j:j) .le. '9' .and. .not. part_started) then
                ! If it is a digit and the part has not started yet, then
                ! set the start position of the part to the current position
                parts(k, 1) = i
                parts(k, 2) = j
                parts(k, 3) = j
                part_started = .true.
            else if (lines(i)(j:j) .ge. '0' .and. lines(i)(j:j) .le. '9' .and. part_started .and. j /= 140) then
                ! If it is a digit and the part has started, then
                ! set the end position of the part to the current position
                parts(k, 3) = j
            else if ((.not. (lines(i)(j:j) .ge. '0' .and. lines(i)(j:j) .le. '9') .or. j == 140) .and. part_started) then
                ! If it is not a digit and the part has started, then
                ! the part has ended, so set part_started to false
                if (j == 140 .and. (lines(i)(j:j) .ge. '0' .and. lines(i)(j:j) .le. '9')) then
                    parts(k, 3) = 140
                end if

                part_started = .false.
                k = k + 1
            end if
        end do
    end do

    last_part = k - 1

    ! Loop through all the parts and check and loop through from each of their start
    ! to their end position and check if any surrounding character is no digit and
    ! not equal to '.' and if so, convert the part number to an integer
    parts_sum = 0
    do i=1,last_part
        part_connected = .false.

        ! Convert the part number to an integer
        part_number_string = lines(parts(i, 1))(parts(i, 2):parts(i, 3))
        read(part_number_string, *) part_number

        do j=parts(i, 2),parts(i, 3)
            do k=max(1, parts(i, 1) - 1),min(parts(i, 1) + 1, 140)
                do l=max(1, j - 1), min(j + 1, 140)
                    if (lines(k)(l:l) .ne. '.' .and. (lines(k)(l:l) .lt. '0' .or. lines(k)(l:l) .gt. '9')) then
                        part_connected = .true.
                        parts_with_gear(i) = gear(l, k, part_number, lines(k)(l:l) .eq. '*')
                    end if
                end do
            end do
        end do

        if (part_connected) then
            parts_sum = parts_sum + part_number
        end if
    end do

    write(*,*) parts_sum

    ! For each part loop through all the parts and check if they are connected
    ! to the same gear and if so, multiply the part numbers into the variable
    ! gear_ratio
    sum_gear_ratios = 0
    do i=1,last_part
        do j=i + 1,last_part
            if (parts_with_gear(i)%connected .and. &
                parts_with_gear(j)%connected .and. parts_with_gear(i)%x == parts_with_gear(j)%x .and. &
                parts_with_gear(i)%y == parts_with_gear(j)%y) then
                sum_gear_ratios = sum_gear_ratios + parts_with_gear(i)%part_number * parts_with_gear(j)%part_number
            end if
        end do
    end do

    write(*,*) sum_gear_ratios
end program AOC3
