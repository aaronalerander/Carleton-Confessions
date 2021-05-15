open Types;

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

let helperDecodeAllConfessions = json =>
  Json.Decode.{
    allConfessionsArray: json |> field("data", array(decodeConfession)),
  };

let helperDecodeData = json =>
  Json.Decode.{
    allConfessions:
      json |> field("allConfessions", helperDecodeAllConfessions),
  };

let helperDecodeConfessionWithCommentsdata = json =>
  Json.Decode.{
    confession: json |> field("findConfessionByID", decodeConfession),
  };

let helperDecodeCreateConfessiondata = json =>
  Json.Decode.{
    confession: json |> field("createConfession", decodeConfession),
  };

let helperDecodeCreateCommentdata = json =>
  Json.Decode.{
    confession: json |> field("parentConfession", decodeConfession),
  };

let decodeGetRecentConfessionsResponse = json =>
  Json.Decode.{data: json |> field("data", helperDecodeData)};

let decodeGetConfessionWithCommentsResponse = json =>
  Json.Decode.{
    confessionWithCommentsdata:
      json |> field("data", helperDecodeConfessionWithCommentsdata),
  };

let decodeCreateConfessionResponse = json =>
  Json.Decode.{
    confessionWithCommentsdata:
      json |> field("data", helperDecodeCreateConfessiondata),
  };

let decodeCreateCommentData = json =>
  Json.Decode.{
    confessionWithCommentsdata:
      json |> field("createComment", helperDecodeCreateCommentdata),
  };

let decodeCreateCommentResponse = json =>
  Json.Decode.{
    confessionWithCommentsResponse:
      json |> field("data", decodeCreateCommentData),
  };
