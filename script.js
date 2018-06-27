var data = {
    datasets: [{
        data: [
            6,
            5,
            4,
            3,
            2
        ],
        backgroundColor: [
            "#FF6384",
            "#4BC0C0",
            "#FFCE56",
            "#E7E9ED",
            "#36A2EB"
        ],
        label: 'My dataset' // for legend
    }],
    labels: [
        "HTML & CSS",
        "JavaScript",
        "C++",
        "Java",
        "PHP"
    ]
};
var ctx = $("#myChart");
new Chart(ctx, {
    data: data,
    type: 'polarArea'
});