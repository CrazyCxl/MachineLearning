function centroids = kMeansInitCentroids(X, K)
%KMEANSINITCENTROIDS This function initializes K centroids that are to be 
%used in K-Means on the dataset X
%   centroids = KMEANSINITCENTROIDS(X, K) returns K initial centroids to be
%   used with the K-Means on the dataset X
%

% You should return this values correctly
centroids = zeros(K, size(X, 2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should set centroids to randomly chosen examples from
%               the dataset X
%

idxs = zeros(K,1);

for i=1:size(centroids,1)
    idx=randi(size(X,1),1);
    while sum(idxs==idx)>0
        idx=randi(size(X,1),1);
    end
    centroids(i,:)=X(idx,:);
    idxs(i)=idx;
end




% =============================================================

end

