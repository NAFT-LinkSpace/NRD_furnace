from control import matlab
from matplotlib import pyplot as plt
import numpy as np


# 同じインスタンスに伝達関数を入れると同じグラフに出してくれる
class PlotManager:
    def __init__(self):
        _fig, self.ax = plt.subplots()

    def set_step_response_of_Tf(self, Tf, time_array, label):
        # (y_array, self.time_array) = matlab.step(Tf, time_array)
        # self.ax.plot(self.time_array, y_array, label=label)
        self.set_impulse_response_of_Tf(
            Tf * matlab.tf([1], [1, 0]), time_array=time_array, label=label
        )

    def set_impulse_response_of_Tf(self, Tf, time_array, label):
        (y_array, self.time_array) = matlab.impulse(Tf, time_array)
        self.ax.plot(self.time_array, y_array, label=label)

    def set_label(self, ylabel):
        self.ax.set(xlabel="t[s]", ylabel=ylabel)
        self.ax.legend()

    def set_title(self, title):
        self.ax.set_title(title)


def printhelper(tag, s):
    print(tag, "=", s, ";")


# Cs:control TranferFunction
# Ps:target TranferFunction
# Gs:total TranferFunction
def simulate(Cs, Ps, Gs, target_input_tf, trange, title_prefix):

    printhelper("target_input_tf", target_input_tf)
    LPF_tf = matlab.tf([1], [5, 1])
    pm_temperature = PlotManager()

    pm_temperature.set_impulse_response_of_Tf(
        Ps * target_input_tf, trange, "no control Tout"
    )
    pm_temperature.set_impulse_response_of_Tf(
        Gs * target_input_tf, trange, "control Tout"
    )
    pm_temperature.set_impulse_response_of_Tf(
        Gs * LPF_tf * target_input_tf, trange, "LPF control Tout"
    )
    # pm_temperature.set_impulse_response_of_Tf(1, trange, "unit step")
    # pm_temperature.set_impulse_response_of_Tf(LPF_tf, trange, "LPF unit step")
    pm_temperature.set_impulse_response_of_Tf(target_input_tf, trange, "target")
    pm_temperature.set_label("T[Cels]")
    pm_temperature.set_title(title_prefix + ":Temperature[Cels]")

    pm_W = PlotManager()

    control_out_tf = Cs / (1 + Cs * Ps)
    pm_W.set_impulse_response_of_Tf(
        control_out_tf * target_input_tf, trange, "control out"
    )
    pm_W.set_impulse_response_of_Tf(
        control_out_tf * LPF_tf * target_input_tf, trange, "LPF control out"
    )
    pm_W.set_label("Q[W]")
    pm_W.set_title(title_prefix + ":energy[W]")


def main():
    resistance_ohm = 29.4
    satirated_temperature_cels = 150
    atmosphere_temperature_cels = 20
    L_delayed_s = 51  # 遅れ時間
    temp_tau_s = 2000  # 1次遅れの時定数

    tau_s = temp_tau_s  # 時定数

    input_to_system_W = 100 ** 2 / resistance_ohm
    A_target_gain = (
        satirated_temperature_cels - atmosphere_temperature_cels
    ) / input_to_system_W

    # https://ja.wikipedia.org/wiki/PID%E5%88%B6%E5%BE%A1#CHR%E6%B3%95

    R_grad = A_target_gain / tau_s
    Kp = 0.6 / (R_grad * L_delayed_s)
    Ti = tau_s
    Td = 0.5 * L_delayed_s

    Ki = Kp / Ti
    Kd = Kp * Td

    printhelper("input_to_system_W", input_to_system_W)
    printhelper("A_target_gain", A_target_gain)

    printhelper("Kp", Kp)
    printhelper("Ki", Ki)
    printhelper("Kd", Kd)

    # Cs = Kp + Ki / s + Kd * s
    Cs = matlab.tf([Kd, Kp, Ki], [1, 0])
    # Ps = A / (tau_s * s +1)
    Ps = matlab.tf([A_target_gain], [tau_s, 1])

    printhelper("Cs", Cs)
    printhelper("Ps", Ps)

    Gs = matlab.feedback(Cs * Ps)
    print("Gs", Gs)

    trange = np.arange(0, 60 * 5, 1)
    target_input_tf = matlab.tf([3], [1, 0])
    simulate(Cs, Ps, Gs, target_input_tf, trange, "step")

    trange = np.arange(0, 60 * 20, 1)
    target_input_tf = matlab.tf([2 / 60], [1, 0, 0])
    simulate(Cs, Ps, Gs, target_input_tf, trange, "lamp")

    plt.show()


# execute main function
main()
