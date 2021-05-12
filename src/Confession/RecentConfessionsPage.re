open Belt;

type state = {
  recentConfessions: ConfessionData.recentConfessions,
  loading: bool,
  fetchError: bool,
};

type action =
  | Loaded(ConfessionData.recentConfessions)
  | Loading
  | FetchErrorOccured(string);

let initialState = {
  recentConfessions: [||],
  loading: true,
  fetchError: false,
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Loading => {...state, loading: true}
        | Loaded(data) =>
          let confessionsNewestToLatest = Array.reverse(data);
          {
            ...state,
            recentConfessions: confessionsNewestToLatest,
            loading: false,
          };
        | FetchErrorOccured(message) => {...state, fetchError: true}
        },
      initialState,
    );

  React.useEffect0(() => {
    let callback = result => {
      switch (result) {
      | None => dispatch(FetchErrorOccured("None"))
      | Some(confessions) => dispatch(Loaded(confessions))
      };
    };
    ConfessionData.fetchConfessions(callback);
    None;
  });

  switch (state) {
  | {fetchError: true} =>
    <div>
      {ReasonReact.string(
         "There was an error, please contact be at aaronalexander.inc@gmail.com",
       )}
    </div>

  | {loading: true} => <div> {ReasonReact.string("Loading...")} </div>

  | {loading: false, fetchError: false} =>
    <div>
      {state.loading
         ? ReasonReact.string("Loading...")
         : {
           state.recentConfessions
           ->Array.mapWithIndex((index, confession) =>
               <ConfessionListItem key={confession.id} index confession />
             )
           ->React.array;
         }}
    </div>
  };
};
