import React, { useEffect, useState } from 'react';
import {
  Alert,
  SafeAreaView,
  View,
  Text,
  TouchableOpacity,
  StyleSheet,
  Platform,
  ActionSheetIOS,
  Image,
  BackHandler,
} from 'react-native';
import {
  EventType,
  useZoom,
  ZoomVideoSdkUser,
  Errors,
} from '@zoom/react-native-videosdk';
import Clipboard from '@react-native-clipboard/clipboard'
import generateJwt from '../utils/jwt';
import { icons } from '../assets/icons';
import size from '../theme/fonts';
import metrics from '../theme/metrics';


export function CallScreen({ navigation, route }) {

  const { params } = route;
  const zoom = useZoom();

  const [isInSession, setIsInSession] = useState(false);
  const [isMuted, setIsMuted] = useState(false);
  const [isSpeakerOn, setIsSpeakerOn] = useState(false);
  const [sessionName, setSessionName] = useState('');
  const [users, setUsersInSession] = useState([]);
  const [token, setToken] = useState("")

  useEffect(() => {
    (async () => {
      const token = await generateJwt(
        params.sessionName,
        1,
        params.zoomAppKey,
        params.zoomAppSecret
      );
      setToken(token)

      try {
        await zoom.joinSession({
          sessionName: params.sessionName,
          sessionPassword: "",
          token: token,
          userName: params.displayName,
          audioOptions: {
            connect: true,
            mute: false,
          },
          videoOptions: {
            localVideoOn: false,
          },
          sessionIdleTimeoutMins: parseInt(params.sessionIdleTimeoutMins, 10),
        });
      } catch (e) {
        Alert.alert('Failed to join the session');
        setTimeout(() => navigation.goBack(), 1000);
      }
    })();
  }, []);

  useEffect(() => {
    const sessionJoinListener = zoom.addListener(
      EventType.onSessionJoin,
      async (session) => {
        setIsInSession(true);
        zoom.session.getSessionName().then(setSessionName);
        const mySelf = new ZoomVideoSdkUser(session.mySelf);
        const remoteUsers = await zoom.session.getRemoteUsers();
        setUsersInSession([mySelf, ...remoteUsers]);
        zoom.audioHelper.setSpeaker(false);
        zoom.audioHelper.unmuteAudio(mySelf.userId);
      }
    );

    const sessionLeaveListener = zoom.addListener(
      EventType.onSessionLeave,
      () => {
        setIsInSession(false);
        setUsersInSession([]);
        navigation.goBack();
      }
    );

    const userAudioStatusChangedListener = zoom.addListener(
      EventType.onUserAudioStatusChanged,
      async () => {
        const mySelf = new ZoomVideoSdkUser(
          await zoom.session.getMySelf()
        );
        mySelf.audioStatus.isMuted().then((muted) => setIsMuted(muted));
      }
    );

    const userJoinListener = zoom.addListener(
      EventType.onUserJoin,
      async ({ remoteUsers }) => {
        const mySelf = await zoom.session.getMySelf();
        const remote = remoteUsers.map(
          (user) => new ZoomVideoSdkUser(user)
        );
        setUsersInSession([mySelf, ...remote]);
      }
    );

    const userLeaveListener = zoom.addListener(
      EventType.onUserLeave,
      async ({
        remoteUsers,
      }) => {
        const mySelf = await zoom.session.getMySelf();
        const remote = remoteUsers.map(
          (user) => new ZoomVideoSdkUser(user)
        );
        setUsersInSession([mySelf, ...remote]);
      }
    );

    const eventErrorListener = zoom.addListener(
      EventType.onError,
      async (error) => {
        console.log('Error: ' + JSON.stringify(error));
        switch (error.errorType) {
          case Errors.SessionJoinFailed:
            Alert.alert('Failed to join the session');
            setTimeout(() => navigation.goBack(), 1000);
            break;
          case null:
            Alert.alert('Failed to join the session');
            setTimeout(() => navigation.goBack(), 1000);
            break;
          default:
        }
      }
    );

    return () => {
      sessionJoinListener.remove();
      sessionLeaveListener.remove();
      userAudioStatusChangedListener.remove();
      userJoinListener.remove();
      userLeaveListener.remove();
      eventErrorListener.remove();
    };
  }, [zoom, route, users]);

  const leaveSession = (endSession) => {
    zoom.leaveSession(endSession);
    navigation.goBack();
  };

  const onPressAudio = async () => {
    const mySelf = await zoom.session.getMySelf();
    const muted = await mySelf.audioStatus.isMuted();
    setIsMuted(muted);
    muted
      ? zoom.audioHelper.unmuteAudio(mySelf.userId)
      : zoom.audioHelper.muteAudio(mySelf.userId);
  };

  const onPressLeave = async () => {
    const mySelf = await zoom.session.getMySelf();
    const options = [
      {
        text: 'Leave Session',
        onPress: () => leaveSession(false),
      },
    ];

    if (mySelf.isHost) {
      options.unshift({
        text: 'End Session',
        onPress: () => leaveSession(true),
      });
    }

    if (Platform.OS === 'ios') {
      ActionSheetIOS.showActionSheetWithOptions(
        {
          options: ['Cancel', ...options.map((option) => option.text)],
          cancelButtonIndex: 0,
        },
        (buttonIndex) => {
          if (buttonIndex !== 0) {
            options[buttonIndex - 1].onPress();
          }
        }
      );
    } else {
      Alert.alert('Do you want to leave this session?', '', options, {
        cancelable: true,
      });
    }
  };

  const onPressSpeaker = async () => {
    zoom.audioHelper.setSpeaker(!isSpeakerOn);
    setIsSpeakerOn(!isSpeakerOn);
  };

  const copyToClipboard = () => {
    Clipboard.setString(
      `callerName: ${params.displayName}\ntoken: ${token}\nchannel: ${params.sessionName}\nsdk: zoom`
    )
  }

  useEffect(() => {
    const backHandler = BackHandler.addEventListener(
      'hardwareBackPress',
      () => {
        return true
      })
    return () => backHandler.remove()
  }, [])

  return (
    <SafeAreaView style={styles.container}>
      <View style={styles.topWrapper}>
        <View style={styles.sessionInfo}>
          <Text
            style={styles.sessionName}
            numberOfLines={3}
          >
            {sessionName}
          </Text>
          <Text style={styles.numberOfUsers}>
            {`Participants: ${users.length}`}
          </Text>
        </View>
      </View>
      <View style={styles.middleWrapper}>
        <TouchableOpacity onPress={onPressAudio} >
          <Image
            source={isMuted ? icons.unmute : icons.mute}
            style={styles.image}
          />
        </TouchableOpacity>
        <TouchableOpacity onPress={onPressSpeaker}>
          <Image
            source={isSpeakerOn ? icons.speakerOff : icons.speakerOn}
            style={styles.image}
          />
        </TouchableOpacity>
        <TouchableOpacity style={styles.copyButton} onPress={copyToClipboard}>
          <Text style={styles.copyText}>Copy Data</Text>
        </TouchableOpacity>
      </View>
      <TouchableOpacity style={styles.leaveButton} onPress={onPressLeave} >
        <Text style={styles.leaveText}>LEAVE</Text>
      </TouchableOpacity>
      {!isInSession && (
        <View style={styles.connectingWrapper}>
          <Text style={styles.connectingText}>Connecting</Text>
        </View>
      )}
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: 'black',
  },
  topWrapper: {
    flex: 1
  },
  sessionInfo: {
    width: metrics.width / 2.4,
    padding: metrics.height / 90,
    borderRadius: metrics.height / 90,
    backgroundColor: 'rgba(255,255,255,0.1)',
    marginTop: metrics.height / 30,
    marginLeft: metrics.width / 36
  },
  sessionName: {
    fontSize: size(16),
    fontWeight: 'bold',
    color: 'white',
  },
  numberOfUsers: {
    fontSize: size(13),
    color: 'white',
  },
  middleWrapper: {
    flex: 4,
    paddingLeft: metrics.width / 36,
    justifyContent: 'center',
  },
  image: {
    width: metrics.width / 7.5,
    height: metrics.width / 7.5
  },
  copyButton: {
    width: metrics.width / 4,
    backgroundColor: 'rgba(255,255,255,0.1)',
    borderRadius: metrics.height / 50,
    justifyContent: 'center',
    alignItems: 'center',
    marginTop: metrics.height / 72
  },
  copyText: {
    color: 'white',
    fontSize: size(15),
    paddingVertical: metrics.height / 60,
  },
  leaveButton: {
    borderRadius: metrics.height / 20,
    backgroundColor: 'rgba(255,255,255,0.1)',
    paddingHorizontal: metrics.width / 7,
    paddingVertical: metrics.height / 50,
    alignSelf: 'center',
    marginBottom: metrics.height / 15,
  },
  leaveText: {
    fontSize: size(25),
    fontWeight: 'bold',
    color: 'red',
    textAlign: 'center'
  },
  connectingWrapper: {
    position: 'absolute',
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: 'black'
  },
  connectingText: {
    fontSize: size(27),
    fontWeight: 'bold',
    color: 'white',
  },
});