#入力生成関数
def inFunc():
    #1時間で1問解いた場合の得点の期待値
    return [
        [10, 10, 10, 10, 10, 10],
        [20, 6, 7, 16, 10, 25],
        [6, 29, 18, 3, 5, 19, 22],
        [10, 26, 8, 19, 7, 8],
        [13, 17, 28, 30, 2, 25],
        [20, 10, 18, 3, 16, 23],
        [6, 29, 11, 12, 30, 12],
        [10, 20, 20, 3, 3, 2],
    ]

def diffFunc():
    #各問題の難易度
    #1が標準
    return [1, 2, 0.8, 0.6, 0.9, 1.5, 1.9, 1.2, 0.5, 1.1, 1, 1.3]

#提出する関数
def memberFunc(indata):
    #Python3
    #提出者名
    return [0,1,2,3,4,5]

def moveFunc(joinedAbility,diff):
    return [
        [0,1,2,3,4,5,6,7,8,9,10,11],
        [2,3,4,5,6,7,8,9,10,11,0,1],
        [4,5,6,7,8,9,10,11,0,1,2,3],
        [6,7,8,9,10,11,0,1,2,3,4,5],
        [8,9,10,11,0,1,2,3,4,5,6,7],
        [10,11,0,1,2,3,4,5,6,7,8,9]
    ]

indata=inFunc()
diff=diffFunc()
member=memberFunc(indata)
result = 0
flag = True
pNum = min(6, len(member))
problems = 12
joined=[False]*pNum
joinedAbility=[]
for i in range(pNum):
    if joined[member[i]]:
        #失格
        flag = False
        result = -1
        break
    joinedAbility.append(indata[member[i]])
if flag:
    Mout = moveFunc(joinedAbility, diff)
    cur=[0]*problems
    action=[0]*pNum
    #120turn(1turn=1min)
    for i in range(120):
        dPrgsSum=[0]*problems
        solverNums=[0]*problems
        #each player
        for j in range(len(Mout)):
            prob = Mout[j][action[j]];
            if (prob < 0) or (prob >= problems):
                continue
            while cur[prob] >= 30:
                action[j] += 1;
                if action[j] == problems:
                    break
                prob = Mout[j][action[j]]
                if prob < 0 or prob >= problems:
                    break
            if prob < 0 or prob >= problems:
                continue
            dPrgsSum[prob] += joinedAbility[j][prob // 2] / 60.0 / diff[prob]
            solverNums[prob]+=1
        for j in range(problems):
            blank = 2
            for k in range(solverNums[j]):
                blank /= 2.0;
            if solverNums[j]:
                probProg = (dPrgsSum[j] / solverNums[j]) * (2.0 - blank)
                cur[j] = min(cur[j] + probProg, 30.0)
    #競技終了
    for i in range(problems):
      result += int(cur[i])
print(result)
