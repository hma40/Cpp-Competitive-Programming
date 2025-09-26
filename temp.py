#!/usr/bin/python3


def hPlace(rr,cc,sseq):
    global board
    global used

    for ii in range(len(sseq)):
        while cc < c and board[rr][cc] not in ['-','d','t','D','T']:
            cc += 1
        if cc == c:
            return False
        used.append([rr,cc,board[rr][cc]])
        board[rr][cc] = sseq[ii]

    return True


def vPlace(rr,cc,sseq):
    global board
    global used

    for ii in range(len(sseq)):
        while rr < r and board[rr][cc] not in ['-','d','t','D','T']:
            rr += 1
        if rr == r:
            return False
        used.append([rr,cc,board[rr][cc]])
        board[rr][cc] = sseq[ii]

    return True


def checkRow(rr,cc):
    global board
    global originalBoard
    global c

    # move right to end of sequence on row
    ee = cc
    while ee < c - 1 and board[rr][ee+1] not in openSpace:
        ee += 1
    # move left to start of sequence on row
    while cc > 0 and board[rr][cc-1] not in openSpace:
        cc -= 1

    # if only one value, not a sequence
    if ee == cc:
        return 0

    # check for non-decreasing or non-increasing
    nonDecreasing = True
    nonIncreasing = True
    for ii in range(cc,ee):
        if board[rr][ii] < board[rr][ii+1]:
            nonDecreasing = False
        if board[rr][ii] > board[rr][ii+1]:
            nonIncreasing = False

    # if neither, then bad sequence
    if not nonDecreasing and not nonIncreasing:
#        print('row not monotonic')
        return -1

    # compute sum of digits with modifiers
    factor = 1
    ssum = 0
    for ii in range(cc,ee+1):
        val = int(board[rr][ii])
        if originalBoard[rr][ii] == 'd':
            val *= 2
        if originalBoard[rr][ii] == 't':
            val *= 3
        if originalBoard[rr][ii] == 'D':
            factor *= 2
        if originalBoard[rr][ii] == 'T':
            factor *= 3
        ssum += val

    # if not a multiple of 3, bad sequence
    if (ssum * factor) % 3 != 0:
#        print('row %3!=0',rr,ssum,factor)
        return -1

    # return score
    return ssum * factor


def checkCol(rr, cc):
    global board
    global originalBoard
    global r

    # move down to end of sequence on col
    ee = rr
    while ee < r - 1 and board[ee+1][cc] not in openSpace:
        ee += 1
    # move up to start of sequence on row
    while rr > 0 and board[rr-1][cc] not in openSpace:
        rr -= 1

    # if only one value, not a sequence
    if ee == rr:
        return 0

    # check for non-decreasing or non-increasing
    nonDecreasing = True
    nonIncreasing = True
    for ii in range(rr, ee):
#        print('.',board[ii][cc])
        if board[ii][cc] < board[ii+1][cc]:
            nonDecreasing = False
        if board[ii][cc] > board[ii+1][cc]:
            nonIncreasing = False
#    print('.',board[ee][cc])
    # if neither, then bad sequence
    if not nonDecreasing and not nonIncreasing:
#        print('col not monotonic')
        return -1

    # compute sum of digits with modifiers
    factor = 1
    ssum = 0
    for ii in range(rr, ee + 1):
        val = int(board[ii][cc])
        if originalBoard[ii][cc] == 'd':
            val *= 2
        if originalBoard[ii][cc] == 't':
            val *= 3
        if originalBoard[ii][cc] == 'D':
            factor *= 2
        if originalBoard[ii][cc] == 'T':
            factor *= 3
        ssum += val

    # if not a multiple of 3, bad sequence
    if (ssum * factor) % 3 != 0:
#        print('col %3!=0',cc)
        return -1

    # return score
    return ssum * factor


def check():
    global board
    global originalBoard
    global used

    points = 0

    rowsTested = []
    colsTested = []

    connected = False
    for ch in used:
        # check sequence in any new row
        if not ch[0] in rowsTested:
            p = checkRow(ch[0],ch[1])
            if p == -1:
                return -1
            rowsTested.append(ch[0])
            points += p
        # check sequence in any new column
        if not ch[1] in colsTested:
            p = checkCol(ch[0],ch[1])
            if p == -1:
                return -1
            colsTested.append(ch[1])
            points += p
        # make sure we are connected to existing numbers
        if ch[0] > 0 and originalBoard[ch[0]-1][ch[1]] not in openSpace:
            connected = True
        if ch[0] < r-1 and originalBoard[ch[0]+1][ch[1]] not in openSpace:
            connected = True
        if ch[1] > 0 and originalBoard[ch[0]][ch[1]-1] not in openSpace:
            connected = True
        if ch[1] < c-1 and originalBoard[ch[0]][ch[1]+1] not in openSpace:
            connected = True

    if not connected:
#        print('disconnected')
        return -1
    else:
        return points


openSpace = ['-','d','t','D','T']

r,c = map(int,input().split(' '))

board = []
originalBoard = []
for i in range(r):
    line = input().split(' ')
    board.append(line)
    originalBoard.append([])
    for b in line:
        originalBoard[i].append(b)

nTiles = int(input())

tiles = input().split(' ')

tiles.sort()

#print(board)
#print(tiles)

seqTried = []

best = 0
for i in range(1,1<<nTiles):
    seq = []
    rev = []
    for j in range(nTiles):
        if (i & (1 << j)) != 0:
            seq.append(tiles[j])
            rev.append(tiles[j])

    rev.reverse()
#    print(seq)

    sj = ''.join(seq)
    rj = ''.join(rev)
    if sj in seqTried or rj in seqTried:
        continue

    seqTried.append(sj)
    seqTried.append(rj)

    # attempt to place horizontally
    for y in range(r):
        for x in range(c):
            if board[y][x] not in openSpace:
                continue
            used = []
            if not hPlace(y,x,seq):
                for ch in used:
                    board[ch[0]][ch[1]] = ch[2]
                break
            pts = check()
            if pts > best:
                best = pts
#            print(y,x,pts,best,used)
            for ch in used:
                board[ch[0]][ch[1]] = ch[2]
            used = []
            if not hPlace(y,x,rev):
                for ch in used:
                    board[ch[0]][ch[1]] = ch[2]
                break
            pts = check()
            if pts > best:
                best = pts
#            print(y,x,pts,best,used)
            for ch in used:
                board[ch[0]][ch[1]] = ch[2]

    # attempt to place vertically
    for x in range(c):
        for y in range(r):
            if board[y][x] not in openSpace:
                continue
            used = []
            if not vPlace(y,x,seq):
                for ch in used:
                    board[ch[0]][ch[1]] = ch[2]
                break
            pts = check()
            if pts > best:
                best = pts
#            print(y,x,pts,best,used)
            for ch in used:
                board[ch[0]][ch[1]] = ch[2]
            used = []
            if not vPlace(y,x,rev):
                for ch in used:
                    board[ch[0]][ch[1]] = ch[2]
                break
            pts = check()
            if pts > best:
                best = pts
#            print(y,x,pts,best,used)
            for ch in used:
                board[ch[0]][ch[1]] = ch[2]

print(best)