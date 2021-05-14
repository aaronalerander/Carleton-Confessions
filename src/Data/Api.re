let faunaUrl = "https://graphql.fauna.com/graphql";

let fetchConfessionsRequestInit = {
  let allConfessionsQueryPayload = Js.Dict.empty();

  Js.Dict.set(
    allConfessionsQueryPayload,
    "query",
    Js.Json.string(Queries.allConfessionsQuery),
  );

  Fetch.RequestInit.make(
    ~method_=Post,
    ~body=
      Fetch.BodyInit.make(
        Js.Json.stringify(Js.Json.object_(allConfessionsQueryPayload)),
      ),
    ~headers=
      Fetch.HeadersInit.make({"Authorization": "Bearer " ++ Env.token}),
    (),
  );
};

let fetchConfessions = callback => {
  Js.Promise.(
    Fetch.fetchWithInit(faunaUrl, fetchConfessionsRequestInit)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> ConfessionData.Decode.decodeGetRecentConfessionsResponse
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
};

let fetchConfessionWithCommentsRequestInit = id => {
  let createConfessionWithCommentsQueryPayload = Js.Dict.empty();
  Js.Dict.set(
    createConfessionWithCommentsQueryPayload,
    "query",
    Js.Json.string(Queries.createConfessionWithCommentsQuery(id)),
  );

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
  );
};

let fetchConfessionWithComments = (id, callback) => {
  Js.Promise.(
    Fetch.fetchWithInit(faunaUrl, fetchConfessionWithCommentsRequestInit(id))
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> ConfessionData.Decode.decodeGetConfessionWithCommentsResponse
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

let createConfessionRequestInit = confession => {
  let createConfessionMutationPayload = Js.Dict.empty();
  Js.Dict.set(
    createConfessionMutationPayload,
    "query",
    Js.Json.string(Queries.createConfessionMutation(confession)),
  );

  Fetch.RequestInit.make(
    ~method_=Post,
    ~body=
      Fetch.BodyInit.make(
        Js.Json.stringify(Js.Json.object_(createConfessionMutationPayload)),
      ),
    ~headers=
      Fetch.HeadersInit.make({"Authorization": "Bearer " ++ Env.token}),
    (),
  );
};

let createConfession = (confession, callback) => {
  Js.Promise.(
    Fetch.fetchWithInit(faunaUrl, createConfessionRequestInit(confession))
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> ConfessionData.Decode.decodeCreateConfessionResponse
         |> (
           decodeCreateConfessionResponse =>
             callback(
               Some(
                 decodeCreateConfessionResponse.confessionWithCommentsdata.
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

let createCommentRequestInit = (id, comment) => {
  let createCommentMutationPayload = Js.Dict.empty();
  Js.Dict.set(
    createCommentMutationPayload,
    "query",
    Js.Json.string(Queries.createCommentMutation(id, comment)),
  );

  Fetch.RequestInit.make(
    ~method_=Post,
    ~body=
      Fetch.BodyInit.make(
        Js.Json.stringify(Js.Json.object_(createCommentMutationPayload)),
      ),
    ~headers=
      Fetch.HeadersInit.make({"Authorization": "Bearer " ++ Env.token}),
    (),
  );
};

let createComment = (id, comment, callback) => {
  Js.Promise.(
    Fetch.fetchWithInit(faunaUrl, createCommentRequestInit(id, comment))
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> ConfessionData.Decode.decodeCreateCommentResponse
         |> (
           decodeCreateConfessionResponse =>
             callback(
               Some(
                 decodeCreateConfessionResponse.confessionWithCommentsResponse.
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
