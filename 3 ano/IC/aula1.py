import pennylane as qml
import matplotlib
import numpy as np

n_qubits = 1

# dev = qml.device("default.qubit", wires=n_qubits, shots=50) 
dev = qml.device("default.qubit", wires=n_qubits) 

@qml.qnode(dev) # Python recognizes this function as a quantum circuit
def circuit():
    # qml.PauliX(wires=0) # PauliX gate applied to the first qubit (inverts the state)
    # qml.PauliZ(wires=0) # PauliZ gate applied to the first qubit (does nothing)

    # qml.Hadamard(wires=0) # Hadamard gate applied to the first qubit (creates a superposition)

    # qml.RY(np.pi/2,wires=0) # Rotation around the Y axis by pi/2 
    qml.RY(2*np.arcsin(np.sqrt(0.2)), wires=0)
    # return qml.probs(wires=0)
    return qml.state()


print(circuit()) # Execute the circuit
# qml.draw_mpl(circuit) # Draw the circuit (need jupyter)