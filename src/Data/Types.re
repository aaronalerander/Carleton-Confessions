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
