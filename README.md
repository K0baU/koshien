# 科学の甲子園 非公式競技
JS実行環境
https://local-judge-system.glitch.me
JS,C++,Python提出環境（JS実行も可能）
https://local-judge-and-submit.glitch.me

## 競技参加者がすること
1. 候補8人の実力をみて、高得点を取りやすそうな6人を決める方法を考える
2. いざ問題を解くとき、参加者6人の実力と問題の難しさを参考にして、それぞれの人が取り組む問題の順番を考える

## 目標
 12問の得点の合計を最大化すること

## ルール
ゲーム内の問題は2問\*6分野の計12問(0から11)で構成され、
i問目はi/2番目(小数点以下切り捨て)の分野の問題です。
1ターン(1分)あたりの進捗は、その問題を解いている参加者の実力に比例し、問題の難易度に反比例します。
問題の難易度の標準は1で、標準的な問題を解くときに時間ちょうどで満点を取れる実力が30です。
n人が同時に1つの問題に取り組むとき、実力は合成されて(n人の実力の平均)\*(2-0.5^n)となります。
すなわちn人全員の実力が全く同じとき、n=1,2,3,...と人数が増えると効率は1倍,1.5倍,1.75倍,...と上がっていきますが、1人あたりの効率は下がっていき、何人いても2倍以上にはなりません。
また、同時に同じ問題を解いているメンバーの間の実力差があまりに大きいと、弱い方は足を引っ張ることになりますが、参加者は他のメンバーが頑張っている横で何もせずに待っていられるような性格ではありません。
足を引っ張ることになっても何かしようとするので、得意分野を解き終わった後の動きも考えておくといいでしょう。

## プログラムの実行フロー
1. inFunc()が呼び出され、8人の実力が与えられる
1. 参加者の書いたmemberFunc()が呼び出され、筆記競技に参加するメンバーを決定する(この時点では、問題の難易度は分からない)
1. diffFunc()が呼び出され、各問題の難易度が与えられる
1. 参加者の書いたmoveFunc()が呼び出され、2で決めた参加者が、それぞれどの順で問題を解くかを決定する
1. 120ターン分のシミュレーションが実行され、結果が出力される

## テンプレートの内容
・include
　iostream/vector/algorithm以外を使いたい人は最上部にincludeを追記？

・inFunc()
 メンバー候補8人の、科目0~5までに対する得意さを返す
 値が大きいほど得意
 テストケースの実行時に呼ばれる
 手元で書き換える必要はなし

・diffFunc()
 問題0~11の難しさを返す
 値が大きいほど時間がかかる
 テストケースの実行時に呼ばれる
 手元で書き換える必要はなし

・memberFunc()
 inFunc()で返された値を受け取る
 8人の候補のうちから筆記競技に参加する6人の番号を返す
 要素数6の1次元配列を返す
 提出する関数なので、いろいろ試すとよい

・moveFunc()
 参加する6人の実力（isFunc()の値のうち、memberFunc()で選ばれた6人の値）および、
 問題0~11の難しさ（diffFunc()）を受け取る
 （問題の難しさは、参加者が見積もった難しさ？）
 6人それぞれについて、12問に手を付ける順番を決めて返す　
 要素数6×12の2次元配列を返す（vec[0]の要素数が12）
 提出する関数なので、いろいろ試すとよい

・main()
 memberFunc(),moveFunc()で決められた値を受け取り、
 1分単位で行動をシミュレートする
 各科目iに対して、問題2×i,2×i+1の2問が用意されている
 問題各題に対して30点、合計360点の配点



 ・templateに使用されている変数
 indata[i][j]:候補iの、問題分野jに対する得意さ
 diff[i]:問題iの難しさ
 member:競技に参加する人の配列
 result:合計得点
 flag:参加者に同じ人が含まれていないかどうか
 pNum:参加者の人数（最大6人）
 problems:問題数（必ず12問）
 joined[i]:候補iが既に選ばれているかどうか
 joinedAbility[i][j]:参加者i(候補iとは限らない)の、問題分野jに対する得意さ 
 Mout[i][j]:参加者iがj番目に手を付ける問題番号
 cur[i]:問題iの現在の進捗度（0~30）
 action[i]:参加者iが既に何問解き終わったか
 dPrgsSum[i]:同じターンに問題iを解く人が産む進捗度の和
 solverNums[i]:同じターンに問題iを解く人の総和

## 入力の生成方法
テンプレートに含まれている入力はサンプルであり、審査時に入力されるものでもなければ、入力の傾向を反映したものでもありません。
適宜書き換えてください。
審査時の入力は以下の規則で行い、全ての提出に対して同じケースを使用する予定です。

#### 選手の実力
チームには各分野のスペシャリストが1人ずつ、ジェネラリストが2人いるものとします。

##### スペシャリスト
選手0,1,2,3,4,5はそれぞれ分野0,1,2,3,4,5のスペシャリストです。
スペシャリストは、自分の得意分野の実力が二項分布B(24\*8,1/8)に従います。
すなわち平均で24,天文学的に低い確率で最大その8倍もの実力を誇ります。
しかし得意分野のはずが絶望的に弱い、名ばかりの無能スペシャリストもごくまれに存在します。
得意分野以外の実力は、二項分布B(12\*8,1/8)に従います。

##### ジェネラリスト
選手6,7はジェネラリストです。
ジェネラリストは、全分野の実力が二項分布B(18\*4,1/4)に従います。
すなわち全分野で平均で18の実力を持ちます。
スペシャリストに比べて実力のばらつきは少なめです。

#### 問題の難易度
あまりに簡単な問題やあまりに難しい問題はボツになるため、難易度は1/4以上4未満になります。
2^(-2から2までの一様な乱数)で決定され、確率分布を対数スケールで表示すると1/4以上4未満の範囲で定数になります。
確率分布を線形スケールで表示すると反比例のグラフの1/4以上4未満の部分になります。

## 審査方法
前述の方法で入力ケースを4つ生成し、全員共通のテストケースとする。（少ない?現実で科学の甲子園に出る機会は、Jrを含めても最大で4回なのです）
各テストケースについて順位を決定し、各プログラムについて最高順位の高い順に総合順位を決めます。
最高順位が同じプログラムは、2番目に高い順位がより高い方を上位とします。（それでも同順位なら、以下同様に、3番目,4番目を比較）
4回の順位の組が同じ場合は、4回の点数の合計が高い順に総合順位を決めます。
