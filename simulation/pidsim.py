from control import matlab
from matplotlib import pyplot as plt
import numpy as np

A = 0.7
tau = 2000
# alpha = -1
# beta = -2


# Ki = alpha * beta * (tau + A * Kd) / A
# Kp = -((tau + A * Kd) * (alpha + beta) - 1) / A
L = 40
R = A / (tau - L)

# step response
# Kp 84.0 Ki 0.04285714285714286 Kd 1680.0

Kp = 1.2 / (R * L)
Ki = Kp / (tau - L)
Kd = Kp * (0.5 * L)

print("Kp", Kp, "Ki", Ki, "Kd", Kd)

# Cs = Kp + Ki / s + Kd * s
Cs = matlab.tf([Kd, Kp, Ki], [1, 0])
Ps = matlab.tf([A], [tau, 1])

print("Cs", Cs, "Ps", Ps)
# Gs = Cs * Ps / (1 + Cs * Ps)
Gs = matlab.feedback(Cs * Ps, 1)
# Gs = Cs
print("Gs", Gs)
print(matlab.margin(Gs))

# input
u = matlab.tf([1], [1, 0, 0])
# u = 130
# * matlab.tf([1], [1, 0])

print("u", u)
r = u * matlab.tf([1], [3, 1])
# r = 130
print("r", r)

trange = np.arange(0, 50, 0.1)
# trange = np.arange(0, 3000, 0.1)

fig, ax = plt.subplots()
(yout, T) = matlab.step(Gs * r, trange, input=15)
ax.plot(T, yout, label="Tout")

(uin, T) = matlab.step(u, trange)
ax.plot(T, uin, label="Tin")

cout, T = matlab.step(1 / (Cs * Ps) * r, trange)
ax.plot(T, cout, label="Q")

# matlab.bode(Gs)
plt.ylim(0, 600)
plt.legend()
plt.show()

# matlab.nyquist(Ps)
# plt.show()

# trange = range(0, 500, 0.5)
# plt.plot(trange, [ft(t) for t in trange])
# plt.show()
