# Requires: scikit-learn, numpy, matplotlib
# In Colab: run `!pip install scikit-learn` if needed

import numpy as np
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE

rng = np.random.RandomState(42)

# Build synthetic data: 3 clusters in 5D, 10 points each (30 points total)
centers = np.array([[0,0,0,0,0], [5,5,5,5,5], [-5,5,-5,5,-5]])
X = []
y = []
for i, c in enumerate(centers):
    X.append(rng.normal(loc=c, scale=0.8, size=(10, 5)))
    y += [i] * 10
X = np.vstack(X)
y = np.array(y)

# Run t-SNE (2D embedding)
tsne = TSNE(
    n_components=2,
    init="pca",
    random_state=42,
    perplexity=5,
    learning_rate=100
)

# Put n_iter here instead:
X_emb = tsne.fit_transform(X)

# Print a few embedded coordinates
print("First 8 embedded points (x, y) with labels:")
for i in range(8):
    print(f"{i}: ({X_emb[i,0]:.3f}, {X_emb[i,1]:.3f}) label={y[i]}")

# Plot (single matplotlib plot)
plt.figure(figsize=(6,5))
plt.scatter(X_emb[:,0], X_emb[:,1], c=y)
for i, label in enumerate(y):
    plt.annotate(str(label), (X_emb[i,0], X_emb[i,1]), fontsize=8, alpha=0.7)
plt.title("t-SNE embedding of 3 clusters (5D -> 2D)")
plt.xlabel("t-SNE dim 1")
plt.ylabel("t-SNE dim 2")
plt.tight_layout()
plt.show()
