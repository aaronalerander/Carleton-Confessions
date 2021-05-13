let faunaUrl = "https://graphql.fauna.com/graphql";

type confessionComment = {
  message: string,
  id: string,
  ts: int,
};

type comments = {commentsArray: array(confessionComment)};

type confession = {
  message: string,
  id: string,
  ts: int,
  comments,
};

//go to rename alot of these

type allConfessions = {allConfessionsArray: array(confession)};

type data = {allConfessions};

type response = {data}; //this needs to be renamed fool

type confessionWithCommentsdata = {confession};

type confessionWithCommentsResponse = {confessionWithCommentsdata};

type testWrapper = {confessionWithCommentsResponse};

type recentConfessions = array(confession); // this is a definition for another file, I should think about moving this

module Decode = {
  let decodeConfessionComment = json =>
    Json.Decode.{
      message: json |> field("message", string),
      id: json |> field("_id", string),
      ts: json |> field("_ts", int),
    };

  let decodeComments = json =>
    Json.Decode.{
      commentsArray: json |> field("data", array(decodeConfessionComment)),
    };

  let decodeConfessions = json =>
    Json.Decode.{
      id: json |> field("_id", string),
      ts: json |> field("_ts", int),
      message: json |> field("message", string),
      comments: json |> field("comments", decodeComments),
    };

  let decodeAllConfessions = json =>
    Json.Decode.{
      allConfessionsArray: json |> field("data", array(decodeConfessions)),
    };

  let decodeData = json =>
    Json.Decode.{
      allConfessions: json |> field("allConfessions", decodeAllConfessions),
    };

  let decodeResponse = json =>
    Json.Decode.{data: json |> field("data", decodeData)};

  //im pretty sure it is decode confession idiot
  let decodeConfessionWithCommentsdata = json =>
    Json.Decode.{
      confession: json |> field("findConfessionByID", decodeConfessions),
    };

  let decodeCreateConfessiondata = json =>
    Json.Decode.{
      confession: json |> field("createConfession", decodeConfessions),
    };

  let decodeCreateCommentdata = json =>
    Json.Decode.{
      confession: json |> field("parentConfession", decodeConfessions),
    };

  let decodeConfessionWithCommentsResponse = json =>
    Json.Decode.{
      confessionWithCommentsdata:
        json |> field("data", decodeConfessionWithCommentsdata),
    };

  let decodeCreateConfessionResponse = json =>
    Json.Decode.{
      confessionWithCommentsdata:
        json |> field("data", decodeCreateConfessiondata),
    };

  let decodeCreateCommentResponse = json =>
    Json.Decode.{
      confessionWithCommentsdata:
        json |> field("createComment", decodeCreateCommentdata),
    };

  let biggerdecodeCreateCommentResponse = json =>
    Json.Decode.{
      confessionWithCommentsResponse:
        json |> field("data", decodeCreateCommentResponse),
    };
};

let allConfessionsQuery = "query {
    allConfessions{
      data{
        _id
        _ts
        message
        comments(_size:2) {
          data{
            message
            _id
            _ts
          }
        }
      }
    }
  }";

let allConfessionsQueryPayload = Js.Dict.empty();

Js.Dict.set(
  allConfessionsQueryPayload,
  "query",
  Js.Json.string(allConfessionsQuery),
);

let createConfessionWithCommentsQuery = id => {
  "query{
    findConfessionByID(id: \""
  ++ id
  ++ "\"){
      _id
      _ts
      message
      comments{
        data{
          message
          _id
          _ts
        }
      }
    }
  }";
};

let createConfessionMutation = confession => {
  "mutation{
  createConfession(data: {
    message: \""
  ++ confession
  ++ "\" }
  ){
    _id
    _ts
    message
    comments{
      data{
          message
          _id
          _ts
    }
  }
  }
}";
};

let createCommentMutation = (id, comment) => {
  "mutation{
    createComment(data: {
      message:\""
  ++ comment
  ++ "\"
      parentConfession: {
        connect: \""
  ++ id
  ++ "\"
      }
    }){
      parentConfession{
        _id
        _ts
        message
        comments{
            data{
                message
                _id
                _ts
            }
        }
      }
    }
  }";
};

//see if you can make these  massive functions smaller for readibility
let fetchConfessions = callback =>
  Js.Promise.(
    Fetch.fetchWithInit(
      faunaUrl,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Js.Json.stringify(Js.Json.object_(allConfessionsQueryPayload)),
          ),
        ~headers=
          Fetch.HeadersInit.make({"Authorization": "Bearer " ++ Env.token}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.decodeResponse
         |> (
           decodedResponse =>
             callback(
               Some(decodedResponse.data.allConfessions.allConfessionsArray),
             )
             |> resolve
         )
       )
    |> catch(_error => callback(None) |> resolve)
    |> ignore
  );
//|> ignore

let fetchConfessionWithComments = (id, callback) => {
  let createConfessionWithCommentsQueryPayload = Js.Dict.empty();
  Js.Dict.set(
    createConfessionWithCommentsQueryPayload,
    "query",
    Js.Json.string(createConfessionWithCommentsQuery(id)),
  );
  Js.Promise.(
    Fetch.fetchWithInit(
      faunaUrl,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Js.Json.stringify(
              Js.Json.object_(createConfessionWithCommentsQueryPayload),
            ),
          ),
        ~headers=
          Fetch.HeadersInit.make({"Authorization": "Bearer " ++ Env.token}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.decodeConfessionWithCommentsResponse
         |> (
           decodeConfessionWithCommentsResponse =>
             callback(
               Some(
                 decodeConfessionWithCommentsResponse.
                   confessionWithCommentsdata.
                   confession,
               ),
             )
             |> resolve
         )
       )
    |> catch(_error => callback(None) |> resolve)
    |> ignore
  );
};

let createConfession = (confession, callback) => {
  let createConfessionMutationPayload = Js.Dict.empty();
  Js.Dict.set(
    createConfessionMutationPayload,
    "query",
    Js.Json.string(createConfessionMutation(confession)),
  );
  Js.Promise.(
    Fetch.fetchWithInit(
      faunaUrl,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Js.Json.stringify(
              Js.Json.object_(createConfessionMutationPayload),
            ),
          ),
        ~headers=
          Fetch.HeadersInit.make({"Authorization": "Bearer " ++ Env.token}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.decodeCreateConfessionResponse
         //|> Decode.decodeConfessionWithCommentsResponse
         |> (
           decodeCreateConfessionResponse =>
             callback(
               Some(
                 decodeCreateConfessionResponse.confessionWithCommentsdata.
                   confession,
               ) //what is above vould be wrong type, confessionWithCommentsdata
             )
             |> resolve
         )
       )
    |> catch(_error => callback(None) |> resolve)
    |> ignore
  );
};

let createComment = (id, comment, callback) => {
  let createCommentMutationPayload = Js.Dict.empty();
  Js.Dict.set(
    createCommentMutationPayload,
    "query",
    Js.Json.string(createCommentMutation(id, comment)),
  );
  Js.Promise.(
    Fetch.fetchWithInit(
      faunaUrl,
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(
            Js.Json.stringify(Js.Json.object_(createCommentMutationPayload)),
          ),
        ~headers=
          Fetch.HeadersInit.make({"Authorization": "Bearer " ++ Env.token}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.biggerdecodeCreateCommentResponse
         //|> Decode.decodeConfessionWithCommentsResponse
         |> (
           decodeCreateConfessionResponse =>
             callback(
               Some(
                 decodeCreateConfessionResponse.confessionWithCommentsResponse.
                   confessionWithCommentsdata.
                   confession,
               ) //what is above vould be wrong type, confessionWithCommentsdata
             )
             |> resolve
         )
       )
    |> catch(_error => callback(None) |> resolve)
    |> ignore
  );
};
