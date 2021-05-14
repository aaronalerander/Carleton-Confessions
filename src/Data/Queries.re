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
