#pragma once
#include <dll.h>
#include "ntoskrnl.h"

// All the definitions go here
#ifdef __cplusplus
namespace lo { namespace advapi32 {	// This namespace contains all the definitions for types and macros
#endif

typedef void (WINAPI *LPSERVICE_MAIN_FUNCTION)( uint32_t dwNumServicesArgs, wchar_t  **lpServiceArgVectors );

typedef struct _SERVICE_TABLE_ENTRY {
	wchar_t						*lpServiceName;
	LPSERVICE_MAIN_FUNCTION		lpServiceProc;
}SERVICE_TABLE_ENTRY, *LPSERVICE_TABLE_ENTRY;

typedef uint32_t (WINAPI *LPHANDLER_FUNCTION_EX)( uint32_t dwControl, uint32_t dwEventType, void *lpEventData, void *lpContext );

typedef struct _SERVICE_STATUS {
	uint32_t   dwServiceType;
	uint32_t   dwCurrentState;
	uint32_t   dwControlsAccepted;
	uint32_t   dwWin32ExitCode;
	uint32_t   dwServiceSpecificExitCode;
	uint32_t   dwCheckPoint;
	uint32_t   dwWaitHint;
} SERVICE_STATUS, *LPSERVICE_STATUS;

typedef struct _SERVICE_STATUS_PROCESS {
	uint32_t   dwServiceType;
	uint32_t   dwCurrentState;
	uint32_t   dwControlsAccepted;
	uint32_t   dwWin32ExitCode;
	uint32_t   dwServiceSpecificExitCode;
	uint32_t   dwCheckPoint;
	uint32_t   dwWaitHint;
	uint32_t   dwProcessId;
	uint32_t   dwServiceFlags;
} SERVICE_STATUS_PROCESS, *LPSERVICE_STATUS_PROCESS;


/// Service State -- for Enum Requests (Bit Mask)
#define SERVICE_ACTIVE                 0x00000001
#define SERVICE_INACTIVE               0x00000002
#define SERVICE_STATE_ALL              (SERVICE_ACTIVE | SERVICE_INACTIVE)

/// Controls
#define SERVICE_CONTROL_STOP                   0x00000001
#define SERVICE_CONTROL_PAUSE                  0x00000002
#define SERVICE_CONTROL_CONTINUE               0x00000003
#define SERVICE_CONTROL_INTERROGATE            0x00000004
#define SERVICE_CONTROL_SHUTDOWN               0x00000005
#define SERVICE_CONTROL_PARAMCHANGE            0x00000006
#define SERVICE_CONTROL_NETBINDADD             0x00000007
#define SERVICE_CONTROL_NETBINDREMOVE          0x00000008
#define SERVICE_CONTROL_NETBINDENABLE          0x00000009
#define SERVICE_CONTROL_NETBINDDISABLE         0x0000000A
#define SERVICE_CONTROL_DEVICEEVENT            0x0000000B
#define SERVICE_CONTROL_HARDWAREPROFILECHANGE  0x0000000C
#define SERVICE_CONTROL_POWEREVENT             0x0000000D
#define SERVICE_CONTROL_SESSIONCHANGE          0x0000000E
#define SERVICE_CONTROL_PRESHUTDOWN            0x0000000F
#define SERVICE_CONTROL_TIMECHANGE             0x00000010
#define SERVICE_CONTROL_TRIGGEREVENT           0x00000020

/// Service State -- for CurrentState
#define SERVICE_STOPPED                        0x00000001
#define SERVICE_START_PENDING                  0x00000002
#define SERVICE_STOP_PENDING                   0x00000003
#define SERVICE_RUNNING                        0x00000004
#define SERVICE_CONTINUE_PENDING               0x00000005
#define SERVICE_PAUSE_PENDING                  0x00000006
#define SERVICE_PAUSED                         0x00000007

/// Controls Accepted  (Bit Mask)
#define SERVICE_ACCEPT_STOP                    0x00000001
#define SERVICE_ACCEPT_PAUSE_CONTINUE          0x00000002
#define SERVICE_ACCEPT_SHUTDOWN                0x00000004
#define SERVICE_ACCEPT_PARAMCHANGE             0x00000008
#define SERVICE_ACCEPT_NETBINDCHANGE           0x00000010
#define SERVICE_ACCEPT_HARDWAREPROFILECHANGE   0x00000020
#define SERVICE_ACCEPT_POWEREVENT              0x00000040
#define SERVICE_ACCEPT_SESSIONCHANGE           0x00000080
#define SERVICE_ACCEPT_PRESHUTDOWN             0x00000100
#define SERVICE_ACCEPT_TIMECHANGE              0x00000200
#define SERVICE_ACCEPT_TRIGGEREVENT            0x00000400

/// Service Control Manager object specific access types
#define SC_MANAGER_CONNECT						0x0001
#define SC_MANAGER_CREATE_SERVICE				0x0002
#define SC_MANAGER_ENUMERATE_SERVICE			0x0004
#define SC_MANAGER_LOCK					0x0008
#define SC_MANAGER_QUERY_LOCK_STATUS   0x0010
#define SC_MANAGER_MODIFY_BOOT_CONFIG  0x0020

#define SC_MANAGER_ALL_ACCESS		(STANDARD_RIGHTS_REQUIRED | SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE | \
										SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_LOCK | SC_MANAGER_QUERY_LOCK_STATUS  | \
										SC_MANAGER_MODIFY_BOOT_CONFIG)
/// Service object specific access type
#define SERVICE_QUERY_CONFIG           0x0001
#define SERVICE_CHANGE_CONFIG          0x0002
#define SERVICE_QUERY_STATUS           0x0004
#define SERVICE_ENUMERATE_DEPENDENTS   0x0008
#define SERVICE_START                  0x0010
#define SERVICE_STOP                   0x0020
#define SERVICE_PAUSE_CONTINUE         0x0040
#define SERVICE_INTERROGATE            0x0080
#define SERVICE_USER_DEFINED_CONTROL   0x0100

#define SERVICE_ALL_ACCESS             (STANDARD_RIGHTS_REQUIRED | SERVICE_QUERY_CONFIG | SERVICE_CHANGE_CONFIG | \
										SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS | SERVICE_START | \
										SERVICE_STOP | SERVICE_PAUSE_CONTINUE | SERVICE_INTERROGATE | \
										SERVICE_USER_DEFINED_CONTROL)

/// Service flags for QueryServiceStatusEx
#define SERVICE_RUNS_IN_SYSTEM_PROCESS  0x00000001

/// Info levels for ChangeServiceConfig2 and QueryServiceConfig2
#define SERVICE_CONFIG_DESCRIPTION              1
#define SERVICE_CONFIG_FAILURE_ACTIONS          2
#define SERVICE_CONFIG_DELAYED_AUTO_START_INFO  3
#define SERVICE_CONFIG_FAILURE_ACTIONS_FLAG     4
#define SERVICE_CONFIG_SERVICE_SID_INFO         5
#define SERVICE_CONFIG_REQUIRED_PRIVILEGES_INFO 6
#define SERVICE_CONFIG_PRESHUTDOWN_INFO         7
#define SERVICE_CONFIG_TRIGGER_INFO             8
#define SERVICE_CONFIG_PREFERRED_NODE           9

/// Info levels for NotifyServiceStatusChange
#define SERVICE_NOTIFY_STATUS_CHANGE_1          1
#define SERVICE_NOTIFY_STATUS_CHANGE_2          2

#define SERVICE_NOTIFY_STATUS_CHANGE            SERVICE_NOTIFY_STATUS_CHANGE_2

/// Service notification masks
#define SERVICE_NOTIFY_STOPPED                  0x00000001
#define SERVICE_NOTIFY_START_PENDING            0x00000002
#define SERVICE_NOTIFY_STOP_PENDING             0x00000004
#define SERVICE_NOTIFY_RUNNING                  0x00000008
#define SERVICE_NOTIFY_CONTINUE_PENDING         0x00000010
#define SERVICE_NOTIFY_PAUSE_PENDING            0x00000020
#define SERVICE_NOTIFY_PAUSED                   0x00000040
#define SERVICE_NOTIFY_CREATED                  0x00000080
#define SERVICE_NOTIFY_DELETED                  0x00000100
#define SERVICE_NOTIFY_DELETE_PENDING           0x00000200

/// The following defines are for service stop reason codes

/// Stop reason flags. Update SERVICE_STOP_REASON_FLAG_MAX when new flags are added.
#define SERVICE_STOP_REASON_FLAG_MIN                            0x00000000
#define SERVICE_STOP_REASON_FLAG_UNPLANNED                      0x10000000
#define SERVICE_STOP_REASON_FLAG_CUSTOM                         0x20000000
#define SERVICE_STOP_REASON_FLAG_PLANNED                        0x40000000
#define SERVICE_STOP_REASON_FLAG_MAX                            0x80000000

/// Microsoft major reasons. Update SERVICE_STOP_REASON_MAJOR_MAX when new codes are added.
#define SERVICE_STOP_REASON_MAJOR_MIN                           0x00000000
#define SERVICE_STOP_REASON_MAJOR_OTHER                         0x00010000
#define SERVICE_STOP_REASON_MAJOR_HARDWARE                      0x00020000
#define SERVICE_STOP_REASON_MAJOR_OPERATINGSYSTEM               0x00030000
#define SERVICE_STOP_REASON_MAJOR_SOFTWARE                      0x00040000
#define SERVICE_STOP_REASON_MAJOR_APPLICATION                   0x00050000
#define SERVICE_STOP_REASON_MAJOR_NONE                          0x00060000
#define SERVICE_STOP_REASON_MAJOR_MAX                           0x00070000
#define SERVICE_STOP_REASON_MAJOR_MIN_CUSTOM                    0x00400000
#define SERVICE_STOP_REASON_MAJOR_MAX_CUSTOM                    0x00ff0000

/// Microsoft minor reasons. Update SERVICE_STOP_REASON_MINOR_MAX when new codes are added.
#define SERVICE_STOP_REASON_MINOR_MIN                           0x00000000
#define SERVICE_STOP_REASON_MINOR_OTHER                         0x00000001
#define SERVICE_STOP_REASON_MINOR_MAINTENANCE                   0x00000002
#define SERVICE_STOP_REASON_MINOR_INSTALLATION                  0x00000003
#define SERVICE_STOP_REASON_MINOR_UPGRADE                       0x00000004
#define SERVICE_STOP_REASON_MINOR_RECONFIG                      0x00000005
#define SERVICE_STOP_REASON_MINOR_HUNG                          0x00000006
#define SERVICE_STOP_REASON_MINOR_UNSTABLE                      0x00000007
#define SERVICE_STOP_REASON_MINOR_DISK                          0x00000008
#define SERVICE_STOP_REASON_MINOR_NETWORKCARD                   0x00000009
#define SERVICE_STOP_REASON_MINOR_ENVIRONMENT                   0x0000000a
#define SERVICE_STOP_REASON_MINOR_HARDWARE_DRIVER               0x0000000b
#define SERVICE_STOP_REASON_MINOR_OTHERDRIVER                   0x0000000c
#define SERVICE_STOP_REASON_MINOR_SERVICEPACK                   0x0000000d
#define SERVICE_STOP_REASON_MINOR_SOFTWARE_UPDATE               0x0000000e
#define SERVICE_STOP_REASON_MINOR_SECURITYFIX                   0x0000000f
#define SERVICE_STOP_REASON_MINOR_SECURITY                      0x00000010
#define SERVICE_STOP_REASON_MINOR_NETWORK_CONNECTIVITY          0x00000011
#define SERVICE_STOP_REASON_MINOR_WMI                           0x00000012
#define SERVICE_STOP_REASON_MINOR_SERVICEPACK_UNINSTALL         0x00000013
#define SERVICE_STOP_REASON_MINOR_SOFTWARE_UPDATE_UNINSTALL     0x00000014
#define SERVICE_STOP_REASON_MINOR_SECURITYFIX_UNINSTALL         0x00000015
#define SERVICE_STOP_REASON_MINOR_MMC                           0x00000016
#define SERVICE_STOP_REASON_MINOR_NONE                          0x00000017
#define SERVICE_STOP_REASON_MINOR_MAX                           0x00000018
#define SERVICE_STOP_REASON_MINOR_MIN_CUSTOM                    0x00000100
#define SERVICE_STOP_REASON_MINOR_MAX_CUSTOM                    0x0000FFFF

/// Info levels for ControlServiceEx
#define SERVICE_CONTROL_STATUS_REASON_INFO      1

/// Service SID types supported
#define SERVICE_SID_TYPE_NONE                                   0x00000000
#define SERVICE_SID_TYPE_UNRESTRICTED                           0x00000001
#define SERVICE_SID_TYPE_RESTRICTED                             ( 0x00000002 | SERVICE_SID_TYPE_UNRESTRICTED )


/// Service trigger types
#define SERVICE_TRIGGER_TYPE_DEVICE_INTERFACE_ARRIVAL               1
#define SERVICE_TRIGGER_TYPE_IP_ADDRESS_AVAILABILITY                2
#define SERVICE_TRIGGER_TYPE_DOMAIN_JOIN                            3
#define SERVICE_TRIGGER_TYPE_FIREWALL_PORT_EVENT                    4
#define SERVICE_TRIGGER_TYPE_GROUP_POLICY                           5
#define SERVICE_TRIGGER_TYPE_CUSTOM                                 20

/// Service trigger data types
#define SERVICE_TRIGGER_DATA_TYPE_BINARY                            1
#define SERVICE_TRIGGER_DATA_TYPE_STRING                            2

typedef struct tagWTSSESSION_NOTIFICATION
{
    uint32_t	cbSize;
    uint32_t	dwSessionId;
} WTSSESSION_NOTIFICATION, *PWTSSESSION_NOTIFICATION;

#ifdef __cplusplus
} }

using namespace lo::advapi32;

extern "C" {
#endif

//----------------------------------------- Function declarations -------------------------------------------

WINBASEAPI intptr_t WINAPI RegisterServiceCtrlHandlerExW( __in wchar_t *lpServiceName,  __in __callback LPHANDLER_FUNCTION_EX lpHandlerProc, void * lpContext );

WINBASEAPI BOOL WINAPI SetServiceStatus( __in intptr_t hServiceStatus, __in LPSERVICE_STATUS lpServiceStatus );

WINBASEAPI BOOL WINAPI StartServiceCtrlDispatcher( const SERVICE_TABLE_ENTRY *lpServiceTable );


#ifdef __cplusplus
}; // end extern "C"

namespace lo { namespace advapi32 {

} }

#endif
