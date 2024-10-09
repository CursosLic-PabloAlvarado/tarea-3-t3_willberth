pkg load control  % Load the control package

% Sampling time (e.g., Ts = 1 for a normalized system)
Ts = 1;  % Replace with the correct sampling time if needed

% Constant term
k_x = 0.0001;

% First biquad coefficients (feedforward and feedback)
b1 = [0.0195213, -0.0193573, 0];  % Numerator coefficients with zero for z^-2 term
a1 = [1, -1.9792, 0.9801];        % Denominator coefficients

% Second biquad coefficients
b2 = [0.0566642, -0.0601341, 0];  % Numerator coefficients with zero for z^-2 term
a2 = [1, -1.9066, 0.9213];        % Denominator coefficients

% Third biquad coefficients
b3 = [-0.0767639, 0.0769582, 0];  % Numerator coefficients with zero for z^-2 term
a3 = [1, -1.8992, 0.9028];        % Denominator coefficients

% Create transfer functions for each biquad stage with the same sampling time
H1 = tf(b1, a1, Ts, 'variable', 'z^-1');  % z-domain transfer function for biquad 1
H2 = tf(b2, a2, Ts, 'variable', 'z^-1');  % z-domain transfer function for biquad 2
H3 = tf(b3, a3, Ts, 'variable', 'z^-1');  % z-domain transfer function for biquad 3

% Combine the transfer functions in parallel and add the constant term
H_total = H1 + H2 + H3 + k_x;

% Plot the pole-zero diagram
figure;
pzmap(H_total);
title('Pole-Zero Diagram of Parallel Biquad Filter');
grid on;
pause();
