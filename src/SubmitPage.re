
type state = {
    input: string,
    submitted: bool
    // isLoading: bool,
    // results: list(repository),
  };

type action =
  | UpdateInput(string)
  | Submit;



[@react.component]
    let make = _ => {

    let (state, dispatch) =
    React.useReducer(
        (state, action) =>
        switch (action) {
        //| UpdateResults(results) => {...state, isLoading: false, results}
        | UpdateInput(newInput) => {...state, input: newInput}
        | Submit => {...state, submitted: true}
        },
        // {input: "", isLoading: false, results: []},
        {input: "", submitted: false},
    );


    <>
        <div>             

        {state.submitted
            ?  <a href={"/"}> {ReasonReact.string("you submitted, click this link to view confessions ")}</a>
            : <form
                onSubmit={event => {
                ReactEvent.Form.preventDefault(event);
                dispatch(Submit);
                //myfunc(state.input);
                let value = state.input;
                Js.log("gonna submit " ++ value )
                let _ = ConfessionData.createConfession(value);
                
                //this is should be sending the data
                // let _ =
                //     //ConfessionData.submitConfession() should be like that
                //     Api.getResults(value)
                //     |> Js.Promise.then_(results => {
                //         //dispatch(UpdateResults(results));
                //         Js.Promise.resolve();
                //     });
                // ();

                }}>
                <label htmlFor="search"> {ReasonReact.string("Search")} </label>
                <textarea
                id="search"
                name="search "
                value={state.input}
                onChange={event => {
                    let value = ReactEvent.Form.target(event)##value;
                    dispatch(UpdateInput(value));

                }}
                />
                <button type_="submit">
                {ReasonReact.string("Submit")}
                </button>
            </form>
            
            
            }









            // <form
            //     onSubmit={event => {
            //     ReactEvent.Form.preventDefault(event);
            //     dispatch(Submit);
            //     //myfunc(state.input);
            //     let value = state.input;
                
            //     //this is should be sending the data
            //     // let _ =
            //     //     //ConfessionData.submitConfession() should be like that
            //     //     Api.getResults(value)
            //     //     |> Js.Promise.then_(results => {
            //     //         //dispatch(UpdateResults(results));
            //     //         Js.Promise.resolve();
            //     //     });
            //     // ();

            //     }}>
            //     <label htmlFor="search"> {ReasonReact.string("Search")} </label>
            //     <textarea
            //     id="search"
            //     name="search "
            //     value={state.input}
            //     onChange={event => {
            //         let value = ReactEvent.Form.target(event)##value;
            //         dispatch(UpdateInput(value));

            //     }}
            //     />
            //     <button type_="submit">
            //     {ReasonReact.string("Submit Search")}
            //     </button>
            // </form>
        </div>
    </>



    //<b>React.string(comment.message)</b>
    // <b>{React.string("Sumbit hi there")}</b>


}