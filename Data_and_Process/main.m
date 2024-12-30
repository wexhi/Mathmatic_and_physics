function main()
    % Load and process data
    data = load_data("ppm2.csv");

    % Total time (in seconds)
    % total_time = 29.179; % Given total time

    % Calculate sampling frequency
    N = height(data); % Total number of samples
    sampling_frequency = 1.863874704410707e+03;
    disp(['Sampling frequency: ', num2str(sampling_frequency), ' Hz']);

    % Create time axis
    time_axis = (0:N-1) / sampling_frequency;

    % Display first and last few rows of data
    disp("First few rows of data:");
    disp(data(1:min(5, height(data)), :));

    disp("Last few rows of data:");
    disp(data(max(1, height(data) - 4):end, :));

    disp("Shape of data:");
    disp(["Rows: " num2str(height(data)) ", Columns: " num2str(width(data))]);

    % Plot data
    figure;
    plot(time_axis, data.ppm_log);
    xlabel('Time (s)');
    ylabel('PPM Log');
    title('PPM Log vs Time');
    grid on;
end

function data = load_data(filename)
    % Read data from CSV file
    raw_data = readtable(filename, 'ReadVariableNames', false);

    % Extract odd rows
    ppm_log = raw_data{1:2:end, 1};  % Odd rows

    % Convert to table
    data = table(ppm_log, 'VariableNames', {'ppm_log'});
end
