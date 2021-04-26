## Documentation:
- Document register field usage
- Document the details of the IC configuration mechanism
- Update the abandoned changelog
- Document the register access challenges, chosen solutions etc.
- Document TMC-API 'promises' (e.g. namespace usage)

## General:
- Improve the IC configuration mechanism
	- Return the config state in periodicJob
	- Add a function to configure all registers at once (for applications where no other task is delayed)
	- Allow overriding hardware-preset registers (fix N_A mechanism shortcomings)
- Change channel parameter to generic userdata
- Add new FIELD format to mask/shift headers