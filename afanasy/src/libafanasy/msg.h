#pragma once

#include <time.h>

#include "afqueue.h"
#include "client.h"

namespace af
{
///   Message - Afanasy communication unit.
/**   Any type of client ( aftalk, afrender), afcmd and afserver communicate through messages.
***   Message can have some data or not, determined on its type.
***   Messages with type greater than or equal to \c Msg::TDATA must have some data to be valid.
***   They must have non zero data pointer and data length greater than zero.
***   Messages with type less than \c Msg::TDATA must not have any data to be valid.
***   They must have NULL data pointer.
**/
class Msg : public Af, public AfQueueItem
{
public:
    /// Default constructor.
    Msg( int msgType = 0, int msgInt = 0, bool i_receiving = false);

    /// Constructor from \c Af class.
    Msg( int msgType, Af * afClass, bool i_receiving = false );

    /// Construct a message and set an address
    Msg( const struct sockaddr_storage * ss);

    Msg( const char * rawData, int rawDataLen, bool i_receiving = false);

    ~Msg();///< Destructor.

    void generateInfoStream( std::ostringstream & stream, bool full = false) const;

    /// To set zero (\c Msg::TNone ) message to some non data message. Return \c true on success.
    bool set( int msgType, int msgInt = 0, bool i_receiving = false);

    /// Write \c Af class to message.
    bool set( int msgType, Af * afClass, bool i_receiving = false);

    /// To set zero (\c Msg::TNone ) message to data message. Return \c true on success.
    bool setData( int i_size, const char * i_msgData, int i_type = TDATA);

    /// To set zero (\c Msg::TNone ) message to QString message. Return \c true on success.
    bool setString( const std::string & qstring);

    /// To set zero (\c Msg::TNone ) message to QStringList message. Return \c true on success.
    bool setStringList( const std::list<std::string> & stringlist);

    /// Get String ( if message type is TString ).
    bool getString( std::string & string);
    const std::string getString();

    /// Get String ( if message type is TStringList ).
    bool getStringList( std::list<std::string> & stringlist);

/**   IMPORTANT!
***   messages with (type < MText) MUST NOT have any data to be valid:
***   (( mdata == NULL) && ( data_len == 0)) ALWAYS !
***   messages with (type >= MText) MUST have some data to be valid:
***   (( mdata != NULL) && ( data_len > 0)) ALWAYS !
**/
   enum Type{
/*------------ NONDATA MESSAGES ----------------------*/
/// Default message with default type - zero. Only this type can be changed by \c set function.
/**/TNULL/**/,
/// Message set to this type itself, when reading.
/**/TVersionMismatch/**/,
/**/TMagicMismatch/**/,
/// Invalid message. This message type generated by constructors if wrong arguments provieded.
/**/TInvalid/**/,

/**/TConfirm/**/,                   ///< Simple answer with no data to confirm something.

/// Request messages, sizes, quantities statistics. Can be requested displayed by anatoly.
/**/TStatRequest/**/,

/**/TConfigLoad/**/,                ///< Reload config file
/**/TFarmLoad/**/,                  ///< Reload farm file
/**/TMagicNumber/**/,               ///< Set new Magic Number


/**/TClientExitRequest/**/,         ///< Request to client to exit,
/**/TClientRestartRequest/**/,      ///< Restart client application,
/**/TClientWOLSleepRequest/**/,     ///< Request to client to fall a sleep,
/**/TClientRebootRequest/**/,       ///< Reboot client host computer,
/**/TClientShutdownRequest/**/,     ///< Shutdown client host computer,

/*- Talk messages -*/
/**/TTalkId/**/,                    ///< Id for new Talk. Server sends it back when new Talk registered.
/**/TTalkUpdateId/**/,              ///< Update Talk with given id ( No information for updating Talk needed).
/**/TTalksListRequest/**/,          ///< Request online Talks list.
/**/TTalkDeregister/**/,            ///< Deregister talk with given id.


/*- Monitor messages -*/
/**/TMonitorId/**/,                 ///< Id for new Monitor. Server sends it back when new Talk registered.
/**/TMonitorUpdateId/**/,           ///< Update Monitor with given id ( No information for updating Monitor needed).
/**/TMonitorsListRequest/**/,       ///< Request online Monitors list.
/**/TMonitorDeregister/**/,         ///< Deregister monitor with given id.

/*- Render messages -*/
/** When Server successfully registered new Render it's send back it's id.**/
/**/TRenderId/**/,
/**/TRendersListRequest/**/,        ///< Request online Renders list message.
/**/TRenderLogRequestId/**/,        ///< Request a log of Render with given id.
/**/TRenderTasksLogRequestId/**/,   ///< Request a log of Render with given id.
/**/TRenderInfoRequestId/**/,       ///< Request a string information about a Render with given id.
/**/TRenderDeregister/**/,          ///< Deregister Render with given id.


/*- Users messages -*/
/**/TUsersListRequest/**/,          ///< Active users information.
/// Uset id. Afanasy sends it back as an answer on \c TUserIdRequest , which contains user name.
/**/TUserId/**/,
/**/TUserLogRequestId/**/,          ///< Request a log of User with given id.
/**/TUserJobsOrderRequestId/**/,    ///< Request User(id) jobs ids in server list order.


/*- Job messages -*/
/**/TJobsListRequest/**/,           ///< Request brief of jobs.
/**/TJobsListRequestUserId/**/,     ///< Request brief of jobs of user with given id.
/**/TJobLogRequestId/**/,           ///< Request a log of a job with given id.
/**/TJobErrorHostsRequestId/**/,    ///< Request a list of hosts produced tasks with errors.
/**/TJobsWeightRequest/**/,         ///< Request all jobs weight.

/// Request a job with given id. The answer is TJob. If there is no job with such id the answer is TJobRequestId.
/**/TJobRequestId/**/,
/// Request a job progress with given id. The answer is TJobProgress. If there is no job with such id the answer is TJobProgressRequestId.
/**/TJobProgressRequestId/**/,

TRESERVED00,
TRESERVED01,
TRESERVED02,
TRESERVED03,
TRESERVED04,
TRESERVED05,
TRESERVED06,
TRESERVED07,
TRESERVED08,
TRESERVED09,

/*---------------------------------------------------------------------------------------------------------*/
/*--------------------------------- DATA MESSAGES ---------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/


/**/TDATA/**/,                      ///< Some data.
/**/TTESTDATA/**/,                  ///< Test some data transfer.
/**/TString/**/,                    ///< String message.
/**/TStringList/**/,                ///< Strings list message.

/**/TStatData/**/,                  ///< Statistics data.

/*- Client messages -*/

/*- Talk messages -*/
/// Register Talk. Send by Talk client to register. Server sends back its id \c TTalkId.
/**/TTalkRegister/**/,
/**/TTalksListRequestIds/**/,       ///< Request a list of Talks with given ids.
/**/TTalksList/**/,                 ///< Message with a list of online Talks.
/**/TTalkDistributeData/**/,        ///< Message with a list Talk's users and a text to send to them.
/**/TTalkData/**/,                  ///< Message to Talk with text.
/**/TTalkExit/**/,                  ///< Ask server to shutdown client application(s),


/*- Monitor messages -*/
/// Register Monitor. Send by Monitor client to register. Server sends back its id \c TMonitorId.
/**/TMonitorRegister/**/,
/**/TMonitorsListRequestIds/**/,    ///< Request a list of Monitors with given ids.
/**/TMonitorsList/**/,              ///< Message with a list of online Monitors.
/**/TMonitorSubscribe/**/,          ///< Subscribe monitor on some events.
/**/TMonitorUnsubscribe/**/,        ///< Unsubscribe monitor from some events.
/**/TMonitorUsersJobs/**/,          ///< Set users ids to monitor their jobs.
/**/TMonitorJobsIdsAdd/**/,         ///< Add jobs ids for monitoring.
/**/TMonitorJobsIdsSet/**/,         ///< Set jobs ids for monitoring.
/**/TMonitorJobsIdsDel/**/,         ///< Delete monitoring jobs ids.
/**/TMonitorMessage/**/,            ///< Send a message (TQString) to monitors with provieded ids (MCGeneral).
/**/TMonitorExit/**/,               ///< Ask server to shutdown client application(s),

/**/TMonitorEvents_BEGIN/**/,       ///< Events types start.

/**/TMonitorJobEvents_BEGIN/**/,    ///< Job events types start.
/**/TMonitorJobsAdd/**/,            ///< IDs of new jobs.
/**/TMonitorJobsChanged/**/,        ///< IDs of changed jobs.
/**/TMonitorJobsDel/**/,            ///< IDs of deleted jobs.
/**/TMonitorJobEvents_END/**/,      ///< Job events types end.

/**/TMonitorCommonEvents_BEGIN/**/, ///< Common events types start.
/**/TMonitorUsersAdd/**/,           ///< IDs of new users.
/**/TMonitorUsersChanged/**/,       ///< IDs of changed users.
/**/TMonitorUsersDel/**/,           ///< IDs of deleted users.
/**/TMonitorRendersAdd/**/,         ///< IDs of new renders.
/**/TMonitorRendersChanged/**/,     ///< IDs of changed renders.
/**/TMonitorRendersDel/**/,         ///< IDs of deleted renders.
/**/TMonitorMonitorsAdd/**/,        ///< IDs of new monitors.
/**/TMonitorMonitorsChanged/**/,    ///< IDs of changed monitors.
/**/TMonitorMonitorsDel/**/,        ///< IDs of deleted monitors.
/**/TMonitorTalksAdd/**/,           ///< IDs of new talks.
/**/TMonitorTalksDel/**/,           ///< IDs of deleted talks.
/**/TMonitorCommonEvents_END/**/,   ///< Common events types end.

/**/TMonitorEvents_END/**/,         ///< Events types end.


/*- Render messages -*/
/** Sent by Render on start, when it's server begin to listen port.
And when Render can't connect to Afanasy. Afanasy register new Render and send back it's id \c TRenderId. **/
/**/TRenderRegister/**/,
/**/TRenderUpdate/**/,              ///< Update Render, message contains its resources.
/**/TRendersListRequestIds/**/,     ///< Request a list of Renders with given ids.
/**/TRendersUpdateRequestIds/**/,   ///< Request a list of resources of Renders with given ids.
/**/TRendersList/**/,               ///< Message with a list of Renders.
/**/TRendersListUpdates/**/,        ///< Message with a list of resources of Renders.
/**/TRenderSetPriority/**/,         ///< Set Render priority,
/**/TRenderSetCapacity/**/,         ///< Set Render capacity,
/**/TRenderSetMaxTasks/**/,         ///< Set Render maximum tasks,
/**/TRenderSetService/**/,          ///< Enable or disable Render service,
/**/TRenderRestoreDefaults/**/,     ///< Restore default Render settings,
/**/TRenderSetNIMBY/**/,            ///< Set Render NIMBY,
/**/TRenderSetUser/**/,             ///< Set Render user,
/**/TRenderSetNimby/**/,            ///< Set Render nimby,
/**/TRenderSetFree/**/,             ///< Set Render free,
/**/TRenderStopTask/**/,            ///< Signal from Afanasy to Render to stop task.
/**/TRenderCloseTask/**/,           ///< Signal from Afanasy to Render to close (delete) finished (stopped) task.
/**/TRenderEjectTasks/**/,          ///< Stop all tasks on Render,
/**/TRenderDelete/**/,              ///< Delete Render from afanasy server container and database,
/**/TRenderRestart/**/,             ///< Restart Render client program,
/**/TRenderWOLSleep/**/,            ///< Ask online render(s) to fall into sleep
/**/TRenderWOLWake/**/,             ///< Ask sleeping render(s) to wake up
/**/TRenderReboot/**/,              ///< Reboot Render host computer,
/**/TRenderShutdown/**/,            ///< Shutdown Render host computer,
/**/TRenderAnnotate/**/,            ///< Set Render annotation,
/**/TRenderExit/**/,                ///< Ask server to shutdown client application(s),
/**/TRenderEjectNotMyTasks/**/,     ///< Stop mot my (based on username of message) tasks on Render,


/*- Users messages -*/
/**/TUsersListRequestIds/**/,       ///< Request a list of Users with given ids.
/**/TUsersList/**/,                 ///< Active users information.
/**/TUserAdd/**/,                   ///< Add a permatent user.
/**/TUserDel/**/,                   ///< Remove a permatent user.
/**/TUserJobsLifeTime/**/,          ///< Set user jobs default life time.
/**/TUserHostsMask/**/,             ///< Set user hosts mask.
/**/TUserHostsMaskExclude/**/,      ///< Set user exclude hosts mask.
/**/TUserMaxRunningTasks/**/,       ///< Set user maximum running tasks number.
/**/TUserPriority/**/,              ///< Set user priority.
/**/TUserErrorsAvoidHost/**/,       ///< Set number of errors on host to avoid it.
/**/TUserErrorRetries/**/,          ///< Set number of automatic retries task with errors.
/**/TUserErrorsTaskSameHost/**/,    ///< Set number of errors for task on same host.
/**/TUserErrorsForgiveTime/**/,     ///< Set time to forgive error host.
/**/TUserIdRequest/**/,             ///< Request an id of user with given name.
/**/TUserMoveJobsUp/**/,            ///< Move jobs one position up in user jobs list.
/**/TUserMoveJobsDown/**/,          ///< Move jobs one position down in user jobs list.
/**/TUserMoveJobsTop/**/,           ///< Move jobs to top position in user jobs list.
/**/TUserMoveJobsBottom/**/,        ///< Move jobs to bottom position up in user jobs list.
/**/TUserJobsOrder/**/,             ///< Jobs ids in server list order.
/**/TUserAnnotate/**/,              ///< Set User annotation,
/**/TUserJobsSolveMethod/**/,       ///< Set jobs solving mode.


/*- Job messages -*/
/**/TJobRegister/**/,               ///< Register job.
/**/TJobStart/**/,                  ///< Start offline (paused) job.
/**/TJobStop/**/,                   ///< Stop job ( stop running tasks and set offline state).
/**/TJobRestart/**/,                ///< Restart job.
/**/TJobRestartErrors/**/,          ///< Restart tasks with errors.
/**/TJobResetErrorHosts/**/,        ///< Reset all job blocks error hosts.
/**/TJobPause/**/,                  ///< Pause job ( set offline state, keep running tasks running).
/**/TJobRestartPause/**/,           ///< Restart and pause job.
/**/TJobDelete/**/,                 ///< Delete a job.
/**/TJobsListRequestIds/**/,        ///< Request a list of Jobs with given ids.
/**/TJobsListRequestUsersIds/**/,   ///< Request brief of jobs od users with given ids.
/**/TJobsList/**/,                  ///< Jobs list information.
/**/TJobProgress/**/,               ///< Jobs progress.
/**/TJobHostsMask/**/,              ///< Set job hosts mask.
/**/TJobHostsMaskExclude/**/,       ///< Set job exclude hosts mask.
/**/TJobDependMask/**/,             ///< Set job depend mask.
/**/TJobDependMaskGlobal/**/,       ///< Set job global depend mask.
/**/TJobMaxRunningTasks/**/,        ///< Set job maximum running tasks number.
/**/TJobMaxRunTasksPerHost/**/,     ///< Set job maximum running tasks per host.
/**/TJobWaitTime/**/,               ///< Set job wait time.
/**/TJobLifeTime/**/,               ///< Set job life time.
/**/TJobPriority/**/,               ///< Set job priority.
/**/TJobNeedOS/**/,                 ///< Set a job os needed.
/**/TJobNeedProperties/**/,         ///< Set a job properties needed.
/**/TJobsWeight/**/,                ///< All jobs weight data.
/**/TJobCmdPost/**/,                ///< Set job post command.
/**/TJobAnnotate/**/,               ///< Set Job annotation,
/**/TJobSetUser/**/,                ///< Change job owner.
/**/TJob/**/,                       ///< Job (all job data).

/**/TBlockDependMask/**/,           ///< Set block depend mask.
/**/TBlockTasksDependMask/**/,      ///< Set block tasks depend mask.
/**/TBlockTasksMaxRunTime/**/,      ///< Set block tasks maximum run time.
/**/TBlockHostsMask/**/,            ///< Set block hosts mask.
/**/TBlockHostsMaskExclude/**/,     ///< Set block exclude hosts mask.
/**/TBlockMaxRunningTasks/**/,      ///< Set block maximum running tasks number.
/**/TBlockMaxRunTasksPerHost/**/,   ///< Set block maximum running tasks number on the same host.
/**/TBlockCommand/**/,              ///< Set block command.
/**/TBlockWorkingDir/**/,           ///< Set block working directory.
/**/TBlockFiles/**/,                ///< Set block files.
/**/TBlockCmdPost/**/,              ///< Set block post command.
/**/TBlockService/**/,              ///< Set block task type.
/**/TBlockParser/**/,               ///< Set block parser type.
/**/TBlockParserCoeff/**/,          ///< Set block parser coefficient.
/**/TBlockResetErrorHosts/**/,      ///< Reset block avoid hosts.
/**/TBlockErrorsAvoidHost/**/,      ///< Set number of errors on host to avoid it.
/**/TBlockErrorRetries/**/,         ///< Set number of automatic retries task with errors.
/**/TBlockErrorsSameHost/**/,       ///< Set number of errors for the task on same host to make task to avoid host.
/**/TBlockErrorsForgiveTime/**/,    ///< Set time to forgive error host.
/**/TBlockCapacity/**/,             ///< Set block capacity.
/**/TBlockCapacityCoeffMin/**/,     ///< Set block capacity minimum coefficient.
/**/TBlockCapacityCoeffMax/**/,     ///< Set block capacity maximum coefficient.
/**/TBlockMultiHostMin/**/,         ///< Set block multihost minimum hosts count.
/**/TBlockMultiHostMax/**/,         ///< Set block multihost maximum hosts count.
/**/TBlockMultiHostWaitMax/**/,     ///< Set block multihost maximum hosts wait time.
/**/TBlockMultiHostWaitSrv/**/,     ///< Set block multihost service start wait time.
/**/TBlockNeedMemory/**/,           ///< Set block render memory need.
/**/TBlockNeedPower/**/,            ///< Set block render power need.
/**/TBlockNeedHDD/**/,              ///< Set block render hdd need.
/**/TBlockNeedProperties/**/,       ///< Set block render properties need.
/**/TBlocksProgress/**/,            ///< Blocks running progress data.
/**/TBlocksProperties/**/,          ///< Blocks progress and properties data.
/**/TBlocks/**/,                    ///< Blocks data.

/**/TTask/**/,                      ///< A task of some job.
/**/TTasksSkip/**/,                 ///< Skip some tasks.
/**/TTasksRestart/**/,              ///< Restart some tasks.
/**/TTaskRequest/**/,               ///< Get task information.
/**/TTaskLogRequest/**/,            ///< Get task information log.
/**/TTaskErrorHostsRequest/**/,     ///< Get task error hosts list.
/**/TTaskOutputRequest/**/,         ///< Job task output request.
/**/TTaskUpdatePercent/**/,         ///< New progress percentage for task.
/**/TTaskUpdateState/**/,           ///< New state for task.
/**/TTaskListenOutput/**/,          ///< Request to send task output to provided address.
/**/TTaskOutput/**/,                ///< Job task output data.
/**/TTasksRun/**/,                  ///< Job tasks run data.

/**/TRESERVED10/**/,
/**/TRESERVED11/**/,
/**/TRESERVED12/**/,
/**/TRESERVED13/**/,
/**/TRESERVED14/**/,
/**/TRESERVED15/**/,
/**/TJSON/**/,                      ///< JSON
/**/TBlockNonSequential/**/,        ///< Set block task solving to non-sequential.
/**/TRenderHideShow/**/,			///< Hide or show renders.
/**/TJobHideShow/**/,				///< Hide or show jobs.

/**/TLAST/**/                       ///< The last type number.
};

    static const char * TNAMES[]; ///< Type names.

    inline int   type()    const { return m_type;  }///< Get message type.
    inline char* data()    const { return m_data;  }///< Get data pointer.
    inline int   dataLen() const { return m_int32; }///< Get data length.
    inline int   int32()   const { return m_int32; }///< Get 32-bit integer, data lenght for data messages.
    inline int   sid()     const { return m_sid;   }///< Get sender id.

	inline void setSid( uint32_t i_sid) { m_sid = i_sid; rw_header( true);}

    inline char* buffer() const { return m_buffer;}///< Get buffer pointer.

    /// Get message full size (with data).
    inline int writeSize() const { return m_type<TDATA ? Msg::SizeHeader : Msg::SizeHeader+m_int32;}

    /// Get buffer at already written postition to write \c size bytes in it.
    char * writtenBuffer( int size);
    inline bool isWriting() const { return  m_writing; } ///< Writing or reading data in message.
    inline bool isReading() const { return !m_writing; } ///< Writing or reading data in message.

    void setInvalid();             ///< Set message invalidness.
    bool readHeader( int bytes);   ///< Read header from message buffer, \c bytes - number of already written bytes in it's buffer.

    inline bool      isNull() const { return m_type == TNULL;    }///< Whether message is null.
    inline bool   isInvalid() const { return m_type == TInvalid; }///< Whether message is invalid.

    void stdOutData( bool withHeader = true);

    static const int SizeHeader;     ///< size of message header.
    static const int SizeBuffer;     ///< message reading buffer size.
    static const int SizeBufferLimit;///< message buffer maximum size.
    static const int SizeDataMax;    ///< maximum data size that can handle a message.

    static const int Version;    ///< Current afanasy version.
    static int Magic;     ///< Current afanasy magick number.

    inline int version() const { return m_version; } ///< Get message afanasy version.

    inline void resetWrittenSize() { m_writtensize = 0; }

    inline bool addressIsEmpty() const { return m_address.isEmpty();}

    inline const size_t addressesCount() const { return m_addresses.size();}

    /// Set to recieve an answer from the same socket after send
    void setReceiving( bool i_value = true ) { m_receive = i_value; }

    /// Set to recieve an answer from the same socket after send
    bool isReceiving() const { return m_receive; }

    /// Set to recieve an answer from the same socket after send
    void setSendFailed( bool i_value = true ) { m_sendfailed = i_value; }

    /// Set to recieve an answer from the same socket after send
    bool wasSendFailed() { return m_sendfailed; }

    /// Set message address
    inline void setAddress( const Address & i_address)
        { m_address = i_address;}

    /// Set message address to \c client
    inline void setAddress( const Client* i_client)
        { m_address = i_client->getAddress();}

    /// Set message address to \c client
    inline void setAddresses( const std::list<Address> & i_addresses)
        { m_addresses = i_addresses;}

    /// Add dispatch address
    inline void addAddress( const Client* client)
        { m_addresses.push_back( client->getAddress());}

    /// Get address constant pointer
    inline const Address & getAddress() const { return m_address;}

    /// Get addresses constant list pointer
    inline const std::list<Address> * getAddresses() const { return &m_addresses;}

    inline void setMagicNumber( int i_number) { m_magic = i_number;}

private:

// header:
    int32_t m_version;   ///< Afanasy network protocol version.
    int32_t m_magic;     ///< Magic number.
    int32_t m_sid;       ///< Sender id.
    int32_t m_type;      ///< Message type.
    int32_t m_int32;     ///< Some 32-bit integer, data length for data messages.

// data poiters:
    char * m_data;       ///< Data pointer.
    char * m_buffer;     ///< Buffer pointer.

// buffering parameters:
    bool m_writing;                  ///< Writing or reading data in message.
    int  m_buffer_size;              ///< Buffer size.
    int  m_data_maxsize;             ///< Data maximum size ( = buffer size - header size).
    int  m_writtensize;              ///< Number of bytes already written in message buffer.

// communication parameters:
    Address m_address;                ///< Address, where message came from or will be send.
    std::list<Address> m_addresses;   ///< Addresses to dispatch message to.
    bool m_receive;                   ///< Whether to recieve an answer on message request.
    bool m_sendfailed;                ///< Message was failed to send.

private:

    void construct();                ///< Called from constuctors.
    bool checkZero( bool outerror ); ///< Check Zero type, data length and pointer.
    bool checkValidness();           ///< Check message header validness;

    /// Allocate memory for buffer, copy \c to_copy_len bytes in new buffer if any
    bool allocateBuffer( int size, int to_copy_len = 0);

    void rw_header( bool write ); ///< Read or write message header.
    void readwrite( Msg * msg);
};
}
