function plotData(X, y)
%PLOTDATA Plots the data points X and y into a new figure 
%   PLOTDATA(x,y) plots the data points with + for the positive examples
%   and o for the negative examples. X is assumed to be a Mx2 matrix.

% Create New Figure
figure; hold on;

% ====================== YOUR CODE HERE ======================
% Instructions: Plot the positive and negative examples on a
%               2D plot, using the option 'k+' for the positive
%               examples and 'ko' for the negative examples.
%









% =========================================================================

p1 = find(y==1);
p2 = find(y==0);

plot(X(p1,1),X(p1,2),'k+','LineWidth',2,'MarkerSize',7);
plot(X(p2,1),X(p2,2),'ko','MarkerFaceColor','y','MarkerSize',7);

hold off;

end
