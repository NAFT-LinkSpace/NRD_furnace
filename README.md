# 温度制御用炉の電装

- 温度制御ができる(PID 制御)
- 設定すれば何でも暖かくできる
- CFRP 加熱成形用として開発した

# 注意

- 高温になりますので十分に安全に配慮して利用してください。
- このプロジェクトは損害賠償その他一切の責任を負担致しません。
- 技術の分かる人のもと利用してください。

# 利用したもの

- Arduino Uno
- Arduino Uno 用シールド用ユニバーサル基板(<https://akizukidenshi.com/catalog/g/gP-06877/>)
- K 型熱電対 ×3
- 熱電対モジュール(MAX31855) ×3
- ソリッド・ステート・リレー（ＳＳＲ）キット(<https://akizukidenshi.com/catalog/g/gK-00203/>)
- 延長コード(もっと良い線を使うべき)

# 環境

- PlatformIO

# 使用法

詳細はそれぞれの項目を参照

- 制御対象のステップ応答から制御対象の時定数と遅れ時間とゲインを得る。
- シミュレーションのコードに定数を代入して実行すると PID ゲインが得られる。
- 制御に必要なパラメータを設定する。
- PlatformIO で Arduino Uno に書き込む。
- UART でコマンドを送れば制御開始
- duty 比一定の出力も可能
- T0,T1,T2 は 3 つの熱電対で測定するそれぞれの温度(3 つ以下でも動く)

# 制御目標の設定

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

# フィードバック対象の設定

[制御設定用ファイル](code/src/control_parameter.hpp)の関数 feedbackTemperature を与えると設定できる。

- 例
  ```c++
  inline double feedbackTemperature(const double T0, const double T1, const double T2, const double elasped_time_s) {
      return T1;
      // return (T0 + T1 + T2) / 3;
  }
  ```

# PWM 周期の設定

[制御設定用ファイル](code/src/control_parameter.hpp)の PWM_PERIOD_ms を与えると設定できる。

# シリアル通信

UART(デフォルト 19200bps)で通信。マイコンからは実行時間、温度、状態、状態に応じた情報が送られる。
状態はコマンドによって遷移する。

SET_DUTY で ConstPWM に遷移したとき

```
now_ms:1001, current temp T0:20.3,T1:20.5,T2:0.0,State:ConstPWM, duty[%]:0.0,
```

START_CONTROL で Control に遷移したとき

| elasped  | target   | heat out             |
| -------- | -------- | -------------------- |
| 経過時間 | 目標温度 | 実際に出力された熱量 |

```
now_ms:1143003, current temp T0:22.3,T1:23.0,T2:0.0,State:Control, elasped[s]:1.9,e(t):-2.9,target[Cels]:20.1,heat out[W]:152.2,duty[%]:44.7,
```

# コマンドの書式

[コマンド設定用ファイル](code/src/keyword.hpp)にあるコマンドをシリアル通信で送れば操作できる。

```
 コマンド コマンド引数 改行コード(CRLF or LF)
```

| コマンドの変数名 | コマンドのデフォルト値 | 引数の型(C/C++) | 引数の範囲               | 引数の単位 | 内容                                                     | 内部状態    |
| ---------------- | ---------------------- | --------------- | ------------------------ | ---------- | -------------------------------------------------------- | ----------- |
| SET_DUTY         | 1                      | float           | 0~100                    | %          | 引数で指定した duty 比を出力する                         | ConstPWM へ |
| START_CONTROL    | 2                      | float           | 0 以上 (省略した場合 0 ) | second     | 引数で指定した時間だけ経過時間を進めてから制御を開始する | Control へ  |

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

## 回路

熱電対を接続し制御対象の温度を測定する。
SSR に繋がったフォトトライアックに PWM を入力し電熱線で制御対象を加熱する。[ピン設定用ファイル](code/src/pin.hpp)で熱電対センサの SPI と PWM 出力のピンアサインを変更可能。[circuit/shield.fzz](circuit/shield.fzz)に Arduino のシールドを熱電対センサと PWM 用のピンをのせている。

## 設計

制御方法やその他

## シミュレーション

matplotlib,numpy,python control に依存したシミュレーションコード。
制御対象のステップ応答から PID ゲインを求めて matplotlib で温度-時間,熱量-時間グラフを書いてくれる。

main 関数の一部

```python
  satirated_temperature_cels = 150 # 収束したときの温度
  atmosphere_temperature_cels = 20 # 大気温度

  # 炉の性能
  resistance_ohm = 29.4 # 電熱線の抵抗値
  L_delayed_s = 51  # 遅れ時間
  temp_tau_s = 2000  # 1次遅れの時定数
  tau_s = temp_tau_s  # 時定数

  input_to_system_W = 100 ** 2 / resistance_ohm # 炉への最大熱量出力

```

実行後のコンソール。以下を[制御設定用ファイル](code/src/control_parameter.hpp)に書き込む。

```
constexpr double MAX_OUTPUT_ENERGY_W = 340.13605442176873 ;
constexpr double Kp = 61.56308677317081 ;
constexpr double Ki = 0.030781543386585404 ;
constexpr double Kd = 1569.8587127158557 ;
```

# 設計

## 制御則

### PID ゲイン設計

[CHR 法](https://ja.wikipedia.org/wiki/PID%E5%88%B6%E5%BE%A1#CHR%E6%B3%95)(オーバーシュート 0%)で設計した。

### 制御器の設計

PID 制御器の実装は速度型 PID で行った。(参考 https://www.nikko-pb.co.jp/products/k_data/P12_13.pdf)
要するに出力に制限があっても(サチっても)ワインドアップしにくい。

## ファームウェア

PlatformIO で開発した Arduino のコード。Arduino Uno 用で開発した。

出力の制御は PWM で実装した。

出力をコントロールするために SSR にフォトトライアックに PWM で信号を送信する。基本的にはデューティ比が出力の熱量と比例するが、利用したフォトトライアックはゼロクロス電力制御が使われているので PWM の周波数は利用する交流電源の周波数より低く設定する必要がある。
~~PFM 制御にしたほうが良かったかもしれないがそうしなかったのは完成するまで気が付かなかったためである。~~

<!-- ### 制御則の設計
1. 制御対象を求める
制御対象を一次遅れ系+無駄時間としてステップ応答を測定した。

PIDゲインを決定した。 -->
