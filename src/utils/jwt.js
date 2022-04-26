import jwt from 'react-native-pure-jwt';


function makeId(length) {
  var result = '';
  var characters =
    'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
  var charactersLength = characters.length;
  for (var i = 0; i < length; i++) {
    result += characters.charAt(Math.floor(Math.random() * charactersLength));
  }
  return result;
}

export default async function generateJwt(
  sessionName,
  roleType,
  zoomaAppKey,
  zoomAppSecret,
) {
  const token = await jwt.sign(
    {
      app_key: zoomaAppKey,
      version: 1,
      user_identity: makeId(10),
      iat: new Date().getTime(),
      exp: new Date(Date.now() + 23 * 3600 * 1000).getTime(),
      tpc: sessionName,
      role_type: parseInt(roleType, 10),
    },
    zoomAppSecret,
    {
      alg: 'HS256',
    }
  );

  return token;
}
