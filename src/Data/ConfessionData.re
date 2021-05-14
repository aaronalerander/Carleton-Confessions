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

type allConfessionsResponse = {data};

type confessionWithCommentsdata = {confession};

type confessionWithCommentsResponse = {confessionWithCommentsdata};

type createCommentResponse = {confessionWithCommentsResponse};

type recentConfessions = array(confession);

module Decode = {
  let decodeConfessionComment = json =>
    Json.Decode.{
      message: json |> field("message", string),
      id: json |> field("_id", string),
      ts: json |> field("_ts", int),
    };

  let decodeComment = json =>
    Json.Decode.{
      commentsArray: json |> field("data", array(decodeConfessionComment)),
    };

  let decodeConfession = json =>
    Json.Decode.{
      id: json |> field("_id", string),
      ts: json |> field("_ts", int),
      message: json |> field("message", string),
      comments: json |> field("comments", decodeComment),
    };

  let helper_decodeAllConfessions = json =>
    Json.Decode.{
      allConfessionsArray: json |> field("data", array(decodeConfession)),
    };

  let helper_decodeData = json =>
    Json.Decode.{
      allConfessions:
        json |> field("allConfessions", helper_decodeAllConfessions),
    };

  let helper_decodeConfessionWithCommentsdata = json =>
    Json.Decode.{
      confession: json |> field("findConfessionByID", decodeConfession),
    };

  let helper_decodeCreateConfessiondata = json =>
    Json.Decode.{
      confession: json |> field("createConfession", decodeConfession),
    };

  let helper_decodeCreateCommentdata = json =>
    Json.Decode.{
      confession: json |> field("parentConfession", decodeConfession),
    };

  let decodeGetRecentConfessionsResponse = json =>
    Json.Decode.{data: json |> field("data", helper_decodeData)};

  let decodeGetConfessionWithCommentsResponse = json =>
    Json.Decode.{
      confessionWithCommentsdata:
        json |> field("data", helper_decodeConfessionWithCommentsdata),
    };

  let decodeCreateConfessionResponse = json =>
    Json.Decode.{
      confessionWithCommentsdata:
        json |> field("data", helper_decodeCreateConfessiondata),
    };

  let decodeCreateCommentData = json =>
    Json.Decode.{
      confessionWithCommentsdata:
        json |> field("createComment", helper_decodeCreateCommentdata),
    };

  let decodeCreateCommentResponse = json =>
    Json.Decode.{
      confessionWithCommentsResponse:
        json |> field("data", decodeCreateCommentData),
    };
};
