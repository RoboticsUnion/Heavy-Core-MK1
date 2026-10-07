import numpy as np

def rpy_to_rotation_matrix(roll, pitch, yaw):
    """Konvertiert Roll-Pitch-Yaw Winkel (in Grad) in eine 3x3 Rotationsmatrix."""
    # Umrechnung in Radiant
    r = np.radians(roll)
    p = np.radians(pitch)
    y = np.radians(yaw)
    
    # Rotationsmatrizen für die einzelnen Achsen
    R_x = np.array([[1, 0, 0],
                    [0, np.cos(r), -np.sin(r)],
                    [0, np.sin(r), np.cos(r)]])
                    
    R_y = np.array([[np.cos(p), 0, np.sin(p)],
210
                    [-np.sin(p), 0, np.cos(p)]])
                    
    R_z = np.array([[np.cos(y), -np.sin(y), 0],
                    [np.sin(y), np.cos(y), 0],
                    [0, 0, 1]])
                    
    # Gesamt-Rotationsmatrix (Reihenfolge: Z-Y-X)
    return R_z @ R_y @ R_x

def inverse_kinematics_6dof(x, y, z, R_06, l1, l2, l4, l6):
    """Berechnet die Inverse Kinematik für einen 6-Achs-Roboter."""
    # 1. Handgelenksmittelpunkt (Wrist Center) berechnen
    P_tcp = np.array([x, y, z])
    z_axis_06 = R_06[:, 2]
    P_wc = P_tcp - l6 * z_axis_06
    
    x_wc, y_wc, z_wc = P_wc[0], P_wc[1], P_wc[2]
    
    # 2. Gelenkwinkel 1, 2, 3 (Positions-IK)
    theta1 = np.arctan2(y_wc, x_wc)
    
    r = np.sqrt(x_wc**2 + y_wc**2)
    s = z_wc - l1
    D = (r**2 + s**2 - l2**2 - l4**2) / (2 * l2 * l4)
    D = np.clip(D, -1.0, 1.0)
    
    theta3 = np.arctan2(-np.sqrt(1 - D**2), D) 
    theta2 = np.arctan2(s, r) - np.arctan2(l4 * np.sin(theta3), l2 + l4 * np.cos(theta3))
    
    # 3. Vorwärtskinematik für R_03
    c1, s1 = np.cos(theta1), np.sin(theta1)
    c23 = np.cos(theta2 + theta3)
    s23 = np.sin(theta2 + theta3)
    
    R_03 = np.array([
        [c1*c23, -c1*s23,  s1],
        [s1*c23, -s1*s23, -c1],
        [  s23,    c23,    0]
    ])
    
    # 4. Gelenkwinkel 4, 5, 6 (Orientierungs-IK)
    R_36 = R_03.T @ R_06
    
    if np.abs(R_36[2, 2]) < 0.9999:
        theta5 = np.arctan2(np.sqrt(R_36[0, 2]**2 + R_36[1, 2]**2), R_36[2, 2])
        theta4 = np.arctan2(R_36[1, 2], R_36[0, 2])
        theta6 = np.arctan2(R_36[2, 1], -R_36[2, 0])
    else:
        theta4 = 0.0
        theta5 = 0.0 if R_36[2, 2] > 0 else np.pi
        theta6 = np.arctan2(-R_36[0, 1], R_36[0, 0])

    return np.array([theta1, theta2, theta3, theta4, theta5, theta6])

# --- BENUTZEREINGABE ÜBER TERMINAL ---
if __name__ == "__main__":
    print("=== Eingabe der Roboter-Abmessungen ===")
    l1 = float(input("Länge Glied 1 (Basis-Höhe) in mm: "))
    l2 = float(input("Länge Glied 2 (Unterarm) in mm: "))
    l4 = float(input("Länge Glied 4 (Oberarm bis Handgelenk) in mm: "))
    l6 = float(input("Länge Glied 6 (Handgelenk bis TCP) in mm: "))

    print("\n=== Eingabe der TCP-Zielpose ===")
    x = float(input("Ziel X-Koordinate: "))
    y = float(input("Ziel Y-Koordinate: "))
    z = float(input("Ziel Z-Koordinate: "))
    
    print("\n=== Eingabe der Orientierung (Euler-Winkel) ===")
    roll = float(input("Roll (Drehung um X in Grad): "))
    pitch = float(input("Pitch (Drehung um Y in Grad): "))
    yaw = float(input("Yaw (Drehung um Z in Grad): "))

    # Berechnung der Rotationsmatrix aus den Winkeln
    R_ziel = rpy_to_rotation_matrix(roll, pitch, yaw)

    # IK berechnen
    try:
        gelenkwinkel_rad = inverse_kinematics_6dof(x, y, z, R_ziel, l1, l2, l4, l6)
        gelenkwinkel_deg = np.degrees(gelenkwinkel_rad)

        print("\n=== Berechnete Gelenkwinkel ===")
        for i, (rad, deg) in enumerate(zip(gelenkwinkel_rad, gelenkwinkel_deg), 1):
            print(f"Achse {i}: {rad:7.4f} rad  ({deg:7.2f}°)")
            
    except Exception as e:
        print("\n[Fehler] Die Position konnte nicht berechnet werden. Eventuell liegt sie außerhalb der Reichweite.")
