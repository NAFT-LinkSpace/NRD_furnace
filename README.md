# 温度制御用炉の電装

- 温度制御ができる(PID 制御)
- 設定すれば何でも暖かくできる
- CFRP 加熱成形用として開発した

## 利用したもの

- Arduino Uno
- Arduino Uno 用シールド用ユニバーサル基板(<https://akizukidenshi.com/catalog/g/gP-06877/>)
- K 型熱電対 ×3
- 熱電対モジュール(MAX31855) ×3
- ソリッド・ステート・リレー（ＳＳＲ）キット(<https://akizukidenshi.com/catalog/g/gK-00203/>)
- 延長コード(もっと良い線を使うべき)

## 環境

- PlatformIO

## 使用法

- 制御で追従させる関数を設定し UART でコマンドを送れば制御開始
- duty 比一定の出力も可能
- T0,T1,T2 は 3 つの熱電対で測定するそれぞれの温度(3 つ以下でも動く)

### 制御目標の設定

[制御設定用ファイル](code/src/control_parameter.hpp)の関数 targetFunction を与えると設定できる。

- 例

  | 時刻[min] | 温度[℃] |
  | --------- | ------- |
  | 0         | 20      |
  | 20        | 40      |
  | 30        | 40      |
  | 50        | 20      |

  - 表のような温度変化を関数で表すと以下のコードのようになる。
  - inflectionPoint は直線で目標の関数を与えるときの変曲点(角)を示す。時間と温度を代入する。
  - 制御終了は`is_end = true`で可能

    ```c++
        struct inflectionPoint {
            double time_s;
            double temp_cels;
        };
        static constexpr inflectionPoint inflectionpoint_s[] = {{0, 20}, {20 * 60, 40}, {30 * 60, 40}, {50 * 60, 20}};

        inline double targetFunction(const double elapsed_time_s, bool& is_end) {
            is_end = false;
            if (elapsed_time_s < inflectionpoint_s[0].time_s) {
                return 0;
            }
            if (elapsed_time_s < inflectionpoint_s[1].time_s) {
                return linear(inflectionpoint_s[0], inflectionpoint_s[1], elapsed_time_s);
            }
            if (elapsed_time_s < inflectionpoint_s[2].time_s) {
                return linear(inflectionpoint_s[1], inflectionpoint_s[2], elapsed_time_s);
            }
            if (elapsed_time_s < inflectionpoint_s[3].time_s) {
                return linear(inflectionpoint_s[2], inflectionpoint_s[3], elapsed_time_s);
            }

            is_end = true;
            return 0.0;
        }

    ```

### フィードバック対象の設定

[制御設定用ファイル](code/src/control_parameter.hpp)の関数 feedbackTemperature を与えると設定できる。

- 例
  ```c++
  inline double feedbackTemperature(const double T0, const double T1, const double T2, const double elasped_time_s) {
      return T1;
      // return (T0 + T1 + T2) / 3;
  }
  ```

### PWM 周期の設定

[制御設定用ファイル](code/src/control_parameter.hpp)の PWM_PERIOD_ms を与えると設定できる。

### 書式

### コマンド コマンド引数 改行コード(CRLF or LF)

[コマンド設定用ファイル](code/src/keyword.hpp)にあるコマンドを UART(19200bps)で送れば操作できる。

| コマンドの変数名 | コマンドのデフォルト値 | 引数の型(C/C++) | 引数の範囲               | 引数の単位 | 内容                                                     |
| ---------------- | ---------------------- | --------------- | ------------------------ | ---------- | -------------------------------------------------------- |
| SET_DUTY         | 1                      | float           | 0~100                    | %          | 引数で指定した duty 比を出力                             |
| START_CONTROL    | 2                      | float           | 0 以上 (省略した場合 0 ) | second     | 引数で指定した時間だけ経過時間を進めてから制御を開始する |

例 コマンドのデフォルト値のとき

- duty 比 20%で出力

  ```
  1 20
  ```

- 経過時間 0 秒から制御開始

  ```
  2
  ```

  もしくは

  ```
  2 0
  ```

- 経過時間 100 秒から制御再開(プログラムが止まったりしたときに途中から再開できる)
  ```
  2 100
  ```

### 回路

熱電対を接続し制御対象の温度を測定する。
SSR に繋がったフォトトライアックに PWM を入力する。[ピン設定用ファイル](code/src/pin.hpp)で熱電対センサの SPI と PWM 出力のピンアサインを変更可能。

## 設計

制御方法やその他

### シミュレーション

python control で書いたシミュレーションコードがある。
制御対象のステップ応答から PID ゲインを求めて matplotlib で温度-時間,熱量-時間グラフを書いてくれる。

### 制御則

[CHR 法](https://ja.wikipedia.org/wiki/PID%E5%88%B6%E5%BE%A1#CHR%E6%B3%95)(オーバーシュート 0%)で設計した。

### ファームウェア

PlatformIO で開発した Arduino のコード。Uno 用で開発した。

出力の制御は PWM で実装した。

出力をコントロールするために SSR にフォトトライアックに PWM で信号を送信する。基本的にはデューティ比が出力の熱量と比例するが、利用したフォトトライアックはゼロクロス電力制御が使われているので PWM の周波数は利用する交流電源の周波数より低く設定する必要がある。
~~PFM 制御にしたほうが良かったがそうしなかったのは完成するまで気が付かなかったためである。~~

<!-- ### 制御則の設計
1. 制御対象を求める
制御対象を一次遅れ系+無駄時間としてステップ応答を測定した。

PIDゲインを決定した。 -->
