# CAD-Files Naming Convention

Each CAD-File is named according to our Naming Convention. This allows us to have relativly compact, but meaningfull names.

<img width="555" height="90" alt="NamingCon_Example" src="https://github.com/user-attachments/assets/32236d63-3144-49c4-81da-34f07d19d03f" />

The file name contains following components:
   - the project name,
   - the subassembly, the file is contained in,
   - a rising part number, starting at 001 for every subassembly (not used for assemblies),
   - the category of the part,
   - the version number

NOTE: In some cases it is possible to put a small clarification (1-2 words) between the part category and version number


# List of available abbreviations

  Project Name:
  - HC1 = HeavyCore MK1 

  Subassembly:
  - BA = Base
  - SH = Shoulder
  - EB = Elbow
  - UPA = Upper arm
  - WR = Wrist
  - GRP = Gripper
  
  Part Category:
  - MT = Mount
  - GR = Gear
  - PLT = Plate
  - SPC = Spacer
  - PIN = Pin
  - HUB = Hub
  - SHAFT = Shaft
  - BRCKT = Bracket

  Exeptions:
  - CM = Common ( this is used for parts that are contained in several subassemblies, but are created for this project and not sourced from outside)
  - ASM = Assembly

# Clarifications

- Plate = mostly used for flat plates that are used as structural elements.
- Mount = used for parts that hold, support, or attach components in place.
- Bracket = used for structural parts that are used to connect, support, or secure components, often at an angle.

Not every subassembly that may be contained in this project has its own abreviation. The prject is divided into 6 subassemblies, one for each axis,
and the common folder, wich is a bit of an exeption. Smaller subassemblies within one of the declared subassemblies must not be specificly labeled in the file names.
However, a new folder can be created to organize files.

<img width="580" height="272" alt="NamingCon_Example1" src="https://github.com/user-attachments/assets/23979bdf-b68f-4ead-9a43-ffcf35b66215" />


Example Assembly File Name:


<img width="515" height="145" alt="NamingCon_Example2" src="https://github.com/user-attachments/assets/b4cc9beb-73ef-4aa5-b3c1-cf75fd92bf0f" />








