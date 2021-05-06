open Belt;

  let faunaUrl = "https://graphql.fauna.com/graphql"

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
  }"

  let allConfessionsQueryPayload = Js.Dict.empty();

  Js.Dict.set(allConfessionsQueryPayload, "query",Js.Json.string(allConfessionsQuery));
  Js.log(allConfessionsQueryPayload);


let createConfessionMutation = (confession) =>{
Js.log("inside createConfessionMutation");
Js.log(confession);
"mutation{
  createConfession(data: {
    message: \"" ++ confession ++ "\" }
  ){
    _id
    _ts
    message
  }
}";
}



//Js.Dict.set(createConfessionMutationPayload, "query",Js.Json.string(createConfessionMutation(confession)));
//Js.log(createConfessionMutationPayload);


type confessionComment = {
  message:string,
  id:string,
  ts:int 
}

type comments = {
   commentsArray : array(confessionComment)
}

type confession = {
  message: string,
  id: string,
  ts:int,
  comments
}

type allConfessions = {
  allConfessionsArray : array(confession)
}

type data = {
  allConfessions
}

type response = {
  data
}

type recentConfessions = array(confession);

let decodeConfessionComment = json =>
  Json.Decode.{
    message:json |> field("message",string),
    id: json |> field("_id", string),
    ts: json |> field("_ts", int)
}

let decodeComments = json =>
  Json.Decode.{
    commentsArray: json |> field("data", array(decodeConfessionComment))
}

let decodeConfessions = json =>
  Json.Decode.{
    message: json |> field("message", string),
    id: json |> field("_id", string),
    ts: json |> field("_ts", int),
    comments: json |> field("comments",decodeComments)
};

let decodeAllConfessions = json =>
  Json.Decode.{
    allConfessionsArray: json |> field("data", array(decodeConfessions))
}

let decodeData = json =>
  Json.Decode.{
    allConfessions: json |> field("allConfessions", decodeAllConfessions)
}

let decodeResponse = json =>
    Json.Decode.{
    data: json |> field("data", decodeData)
}

let fetchConfessions = (callback) =>
  Js.Promise.(
    Fetch.fetchWithInit(faunaUrl,
    Fetch.RequestInit.make(
           ~method_= Post,
           ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(allConfessionsQueryPayload))),
           ~headers = Fetch.HeadersInit.make({"Authorization" : "Bearer fnAEIZfYiPACBESKBQfn85i6_kS91Z7d6kMlb5Rj"}),
           ()
    ))
    |> then_(Fetch.Response.json)
    |> then_(json =>
      json |> decodeResponse
         |> (decodedResponse => callback(decodedResponse.data.allConfessions.allConfessionsArray)
         |> resolve
      )
    // |> then_(json => {
    //   Js.log("this is above")
    //   Js.log(Some(json))
    //   callback(json);  
    // // callback("hello world fetch confessions");
    //   resolve();}
    ) 
    |> ignore
  ); 





  let createConfession = (confession) =>{
  Js.log(confession)
  Js.log(createConfessionMutation(confession))
    //Js.log("inside here with confession " ++ confession)
  let createConfessionMutationPayload = Js.Dict.empty();
  Js.Dict.set(createConfessionMutationPayload, "query",Js.Json.string(createConfessionMutation(confession)))
  Js.Promise.(
    Fetch.fetchWithInit(faunaUrl,
      Fetch.RequestInit.make(
            ~method_= Post,
            ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(createConfessionMutationPayload))),
            ~headers = Fetch.HeadersInit.make({"Authorization" : "Bearer fnAEIZfYiPACBESKBQfn85i6_kS91Z7d6kMlb5Rj"}),
            ()
      )
    )

    |> then_(Fetch.Response.json)
    |> then_(text => Js.log(text) |> resolve)

    ) 
  }
  //)