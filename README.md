# LocalHostUWP

This repo contains a sample UWP app that demonstrates how to connect and receive data from a server running on the localhost. UWP apps are not able to access localhost. By using a windowless
Win32 C++ app and UWP protocols, it is possible to connect to the localhost and receive data in the UWP app.

# Getting Started

The following applications are required to be installed:

* Visual Studio 2017 with Windows Universal App Development package installed
* Windows SDK version 17763 (installed with Visual Studio 2017)
* Python or some other means for running a localhost http server

# Build and Run

1. Open a command prompt and start a Python SimpleHttpServer

```console
cd LocalHostUWP
python -m SimpleHTTPServer 8000
```

1. Open the LocalHostUWP.sln with Visual Studio 2017

1. Select the x64/Debug configuration

1. Set PackagingProject as the Startup Project

1. Double-click on the Package.appxmanifest file in the LocalHostUWP project. 

	* Navigate to the Packaging tab
	
	* Click on Choose Certificate...
	
	* Click on Configure Certificate...
	
	* Select Create test certificate...
	
	* Click on OK (do not enter a password)
	
1. Build the solution

1. Run the LocalHostUWP application.

1. Click on the Test button

1. The contents of the file test.json (served from a localhost http server) will be displayed in the UWP app window



##  Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.microsoft.com.

When you submit a pull request, a CLA-bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., label, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.


## Reporting Security Issues

Security issues and bugs should be reported privately, via email, to the Microsoft Security
Response Center (MSRC) at [secure@microsoft.com](mailto:secure@microsoft.com). You should
receive a response within 24 hours. If for some reason you do not, please follow up via
email to ensure we received your original message. Further information, including the
[MSRC PGP](https://technet.microsoft.com/en-us/security/dn606155) key, can be found in
the [Security TechCenter](https://technet.microsoft.com/en-us/security/default).
