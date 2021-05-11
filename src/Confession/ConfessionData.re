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

type allConfessions = {allConfessionsArray: array(confession)};

type data = {allConfessions};

type response = {data};

type confessionWithCommentsdata = {confession};

type confessionWithCommentsresponse = {confessionWithCommentsdata};

type recentConfessions = array(confession);

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
      message: json |> field("message", string),
      id: json |> field("_id", string),
      ts: json |> field("_ts", int),
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

  let decodeConfessionWithCommentsdata = json =>
    Json.Decode.{
      confession: json |> field("findConfessionByID", decodeConfessions),
    };

  let decodeConfessionWithCommentsResponse = json =>
    Json.Decode.{
      confessionWithCommentsdata:
        json |> field("data", decodeConfessionWithCommentsdata),
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
      _id
      _ts
      message
    }
  }";
};

let fetchConfessions = callback =>
  Js.Promise.
    (
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
                 decodedResponse.data.allConfessions.allConfessionsArray,
               )
               |> resolve
           )
         )
      // |> catch(_error => resolve(None))
      |> catch(_error => resolve(None))
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
               decodeConfessionWithCommentsResponse.confessionWithCommentsdata.
                 confession,
             )
             |> resolve
         )
       )
    |> ignore
  );
};

let createConfession = confession => {
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
    |> resolve
  );
};

let createComment = (id, comment) => {
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
    |> resolve
  );
};
