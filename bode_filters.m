% Load filter matrices from .mat files and navigate between their Bode plots
pkg load signal % Ensure the signal package is loaded

% Define the folder where the .mat files are stored
folder_path = './mat-files/'; % This should now match your folder structure

% Get list of .mat files in the folder
mat_files = dir(fullfile(folder_path, '*.mat'));

% Check if there are any files in the folder
if isempty(mat_files)
    error('No .mat files found in the specified folder.');
end

% Load filter data into memory, keeping track of file names
filters = {};
file_names = {};
for i = 1:length(mat_files)
    file_path = fullfile(folder_path, mat_files(i).name);
    data = load(file_path);
    
    % Load the variable 'SOS' directly
    if isfield(data, 'SOS')
        filters{i} = data.SOS;
        file_names{i} = mat_files(i).name; % Save the file name
    else
        error('The .mat file does not contain an SOS matrix.');
    end
end

% Function to plot Bode plot for a given filter SOS matrix and title
function plot_bode(sos, title_str)
    % Convert the SOS matrix to numerator and denominator form
    [B, A] = sos2tf(sos);
    
    % Get the frequency response
    [h, w] = freqz(B, A, 1024); % Bode plot using the transfer function
    
    % Plot the magnitude and phase response with a logarithmic frequency scale
    figure;
    
    % Magnitude Response (dB)
    subplot(2, 1, 1);
    semilogx(w / pi, 20 * log10(abs(h))); % Use semilogx for logarithmic scale
    title(['Magnitude Response (dB) - ' title_str]);
    xlabel('Normalized Frequency (\times\pi rad/sample)');
    ylabel('Magnitude (dB)');
    ylim([-60, 3]); % Scale the magnitude axis from -60 dB to 3 dB
    grid on; % Add grid

    % Phase Response (radians)
    subplot(2, 1, 2);
    semilogx(w / pi, unwrap(angle(h))); % Use semilogx for logarithmic scale
    title('Phase Response');
    xlabel('Normalized Frequency (\times\pi rad/sample)');
    ylabel('Phase (radians)');
    grid on; % Add grid
end

% Initialize filter index and plot the first filter
current_index = 1;
plot_bode(filters{current_index}, file_names{current_index});

% Infinite loop to listen for user input to switch between filters
printf('Press the left or right arrow keys (or "q" to quit) to switch between filters.\n');
while true
    user_input = input('Left (l), Right (r), or Quit (q): ', 's'); % Prompt user for input
    
    if strcmpi(user_input, 'l') % Left key (l)
        current_index = mod(current_index - 2, length(filters)) + 1;
        close all;
        plot_bode(filters{current_index}, file_names{current_index});
    elseif strcmpi(user_input, 'r') % Right key (r)
        current_index = mod(current_index, length(filters)) + 1;
        close all;
        plot_bode(filters{current_index}, file_names{current_index});
    elseif strcmpi(user_input, 'q') % Quit key (q)
        break;
    else
        printf('Invalid input. Use "l" for left, "r" for right, or "q" to quit.\n');
    end
end
