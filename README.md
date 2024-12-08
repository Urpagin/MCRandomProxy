# Minecraft Random Proxy  

[Demo Video](https://github.com/Urpagin/MCRandomProxy/assets/72459611/47de9c00-a61d-49e8-aa8c-d7ce70481680
)

## Why & How?  

1. **Setup the Port and Server List**  
   - Choose a port to expose the app (e.g., `25565`).  
   - Create a file named `servers.txt` containing a list of Minecraft servers in the following format:  
     ```txt  
     IPv4:port  
     IPv4:port  
     IPv4:port  
     ...  
     ```  
     > *(Ensure `servers.txt` is located next to the binary.)*  

2. **Run the App**  
   - Start the program, then connect to it via your Minecraft client.  
   - If the app is running on the same machine as your client, use the following address: `127.0.0.1:<port_you_chose>`.  
   - Each new connection will randomly route you to one of the servers listed in `servers.txt`.  

3. **How It Works**  
   - The program uses the Asio networking library (C++) to route incoming packets from your client to a randomly selected server and back.  
   - While the program has the potential to read or modify packets, it currently only forwards them without changes.  

---

## Installation  

### Linux 🐧  
- **Prebuilt Binary:** Available for x64 systems.  
- **Other Architectures:** Build the application manually:  
  1. Clone the repository:  
     ```bash  
     git clone https://github.com/Urpagin/MCRandomProxy && cd MCRandomProxy  
     ```  
  2. Create a build directory:  
     ```bash  
     mkdir build && cd build  
     ```  
  3. Build the program:  
     ```bash  
     cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build . --config Release -- -j 16  
     ```  
     After building, run the program (`./MCRandomProxy`) and place the `servers.txt` file next to the binary.  

  4. Create and populate `servers.txt`:  
     ```bash  
     vim servers.txt  
     ```  

### Windows 🪟  
- **Prebuilt Binary:** Available for x64 systems.  
- **Dependency:** Install Microsoft Visual C++ Redistributable (vcredist):  
  - [Direct Download](https://aka.ms/vs/17/release/vc_redist.x86.exe)  
  - [Microsoft VC++ Redistributable Page](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022)  

### macOS 🍎  
- No prebuilt binary available. You must build the program manually.  

### Docker 🐳  
- *Perhaps in the distant future.*  
