import qrcode
import numpy as np

def generate_qr_matrix(link):
    # Create a QR Code with version=1 (21x21), error correction level L
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=1,
        border=0  # No border so matrix is exactly 21x21
    )
    qr.add_data(link)
    qr.make(fit=True)

    # Get the matrix (list of lists of bools)
    matrix = qr.get_matrix()
    
    # Convert bools to binary (0/1)
    binary_matrix = np.array([[1 if cell else 0 for cell in row] for row in matrix])
    
    return binary_matrix

# Example usage
link = "bit.ly/4d0YU0U"  # Keep it short to fit in version 1
matrix = generate_qr_matrix(link)

# Print matrix
for row in matrix:
    print("".join(str(bit) for bit in row))
