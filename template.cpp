#include<iostream>
#include<vector>
#include<algorithm>

//入力生成関数
std::vector<std::vector<double>> inFunc(){
  //1時間で1問解いた場合の得点の期待値
  return {
    {10, 10, 10, 10, 10, 10},
    {20, 6, 7, 16, 10, 25},
    {6, 29, 18, 3, 5, 19, 22},
    {10, 26, 8, 19, 7, 8},
    {13, 17, 28, 30, 2, 25},
    {20, 10, 18, 3, 16, 23},
    {6, 29, 11, 12, 30, 12},
    {10, 20, 20, 3, 3, 2},
  };
}
std::vector<double> diffFunc(){
  //各問題の難易度
  //1が標準
  return {1, 2, 0.8, 0.6, 0.9, 1.5, 1.9, 1.2, 0.5, 1.1, 1, 1.3};
}

//提出する関数
std::vector<int> memberFunc(std::vector<std::vector<double>> indata){
  //c++
  //提出者名
  return {0,1,2,3,4,5};
}
std::vector<std::vector<int>> moveFunc(std::vector<std::vector<double>> joinedAbility,std::vector<double> diff){
  return {
    {0,1,2,3,4,5,6,7,8,9,10,11},
    {2,3,4,5,6,7,8,9,10,11,0,1},
    {4,5,6,7,8,9,10,11,0,1,2,3},
    {6,7,8,9,10,11,0,1,2,3,4,5},
    {8,9,10,11,0,1,2,3,4,5,6,7},
    {10,11,0,1,2,3,4,5,6,7,8,9}
  };
}

int main(){
  std::vector<std::vector<double>> indata=inFunc();
  std::vector<double> diff=diffFunc();
  std::vector<int> member=memberFunc(indata);
  
  double result = 0;
  bool flag = true;
  int pNum = std::min(6, int(member.size()));
  int problems = 12;
  std::vector<bool> joined(pNum,false);
  std::vector<std::vector<double>> joinedAbility;
  for (int i = 0; i < pNum; i++) {
    if (joined[member[i]]) {
      //失格
      flag = false;
      result = -1;
      break;
    }
    joinedAbility.push_back(indata[member[i]]);
  }
  if (flag) {
    std::vector<std::vector<int>> Mout = moveFunc(joinedAbility, diff);
    std::vector<double> cur(problems,0);
    std::vector<int> action(pNum,0);
    //120turn(1turn=1min)
    for (int i = 0; i < 120; i++) {
      std::vector<double> dPrgsSum(problems,0);
      std::vector<int> solverNums(problems,0);
      //each player
      for (int j = 0; j < Mout.size(); j++) {
        int prob = Mout[j][action[j]];
        if (prob < 0 || prob >= problems) {
          continue;
        }
        // if (cur[prob] == 30) {
        //   prob++;
        //   Mout[j][action[j]]++;
        // }
        while(cur[prob]>=30){
          action[j]++ ;
          if(action[j]==problems){
            // 担当問題をすべて解き終えた
              break ;
          }else{
              prob = Mout[j][action[j]] ;
              if(prob < 0 || prob >= problems){
                break ;
              }
          }
        }
        if(prob < 0 || prob >= problems){
          continue ;
        }
        dPrgsSum[prob] += joinedAbility[j][prob / 2] / 60.0 / (double)diff[prob];
        solverNums[prob]++;
      }
      for (int j = 0; j < problems; j++) {
        double blank = 2;
        for (int k = 0; k < solverNums[j]; k++) {
          blank /= 2.0;
        }
        if (solverNums[j]) {
          double probProg = (dPrgsSum[j] / (double)solverNums[j]) * (2.0 - blank);
          cur[j] = std::min(cur[j] + probProg, 30.0);
        }
      }
    }
    //競技終了
    for (int i = 0; i < problems; i++) {
      result += (int)cur[i];
    }
  }
  std::cout << result;
}
